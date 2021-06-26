/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:18:43 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/26 15:33:44 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VirtualServer.hpp"

VirtualServer::VirtualServer(std::string server_name, std::string ip, size_t port)
	: _server_name(server_name), _ip(ip), _port(port)
{
	if (ip.empty())
		_ip = "127.0.0.1";
}

VirtualServer::~VirtualServer() {}

void VirtualServer::addErrorPage(int code, std::string path)
{
	_error_pages[code] = path;
}

void VirtualServer::setMaxBodySize(size_t size) {_client_max_body_size = size;}

std::string VirtualServer::getServerName()
{
	return (_server_name);
}

std::string VirtualServer::getIp()
{
	return (_ip);
}

size_t VirtualServer::getPort()
{
	return (_port);
}

bool compLocation(Location a, Location b)
{
	return (a.getPrefix().length() > b.getPrefix().length());
}

void VirtualServer::addLocation(Location location) {
	location.setServerName(_server_name);
	_locations.push_back(location);
	if (_locations.size() > 1)
		std::sort(_locations.begin(), _locations.end(), compLocation);
}

void VirtualServer::formErrorTask(Task* task, size_t code, std::string reason)
{
	File* error_file = new File(_error_pages[code], false);
	if (!error_file->isOpen())
	{
		task->changeJob(GENERATE_ERROR_PAGE, HTTPResponse(code, reason));
		return ;
	}
	task->changeJob(GET_FILE_CONTENT, error_file, HTTPResponse(code, reason));
}

void VirtualServer::processRequest(HTTPRequest request, Task* task)
{
	std::vector<Location>::iterator it = _locations.begin();
	for (; it != _locations.end(); ++it)
	{
		Path response_path = (*it).checkLocation(request.getPath());
		if (!response_path.empty())
		{
			if (!it->checkAllowedMethods(request.getMethod()))
			{
				formErrorTask(task, 405, "Method Not Allowed");
				return ;
			}
			else if (request.getMethod() == POST)
			{
				if (request.bodyLength() > it->getMaxBodySize())
				{
					formErrorTask(task, 413, "Request Entity Too Large");
					return ;
				}
				File *file = new File(response_path.toStr(), true);
				if (!file->isOpen())
				{
					formErrorTask(task, 500, "Internal Server Error");
					return ;
				}
				int code = 200;
				if (file->wasCreated() == true)
					code = 201;
				task->changeJob(UPLOAD, file, it->getUploadPath(request.getPath()), request.getBody(), HTTPResponse(code, "OK"));
				return ;
			}
			else if (request.getMethod() == DELETE)
			{
				File* file = new File(response_path.toStr(), false);
				if (!file->isOpen())
				{
					formErrorTask(task, 404, "Not Found");
					return ;
				}
				task->changeJob(DELETE_FILE, file, HTTPResponse(200, "OK"));
				return ;
			}
			else if (it->autoindex() && (response_path.directory() || Directory::str_is_dir(response_path.toStr())))
			{
				task->changeJob(AUTOINDEX, new Directory(response_path.toStr()), HTTPResponse(200, "OK"));
				return ;
			}
			else
			{
				response_path.addSegment(it->getIndex());
				if (!it->getIndex().empty())
					response_path.setIsDirectory(false);
				File* file = new File(response_path.toStr(), false);
				if (!file->isOpen())
				{
					formErrorTask(task, 404, "Not Found");
					return ;
				}
				if (request.getMethod() == HEAD)
					task->changeJob(EMPTY_BODY, file, HTTPResponse(200, "OK"));
				else
					task->changeJob(GET_FILE_CONTENT, file, HTTPResponse(200, "OK"));
				return ;
			}
		}
	}
	formErrorTask(task, 404, "Not Found");
	return ;
}
