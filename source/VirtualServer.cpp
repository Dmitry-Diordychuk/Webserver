/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:18:43 by kdustin           #+#    #+#             */
/*   Updated: 2021/07/03 01:05:55 by kdustin          ###   ########.fr       */
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

void VirtualServer::formErrorTask(size_t code, std::string reason, Task *task)
{
	File* error_file = new File(_error_pages[code], false);
	if (!error_file->isOpen())
	{
		task->changeJob(
			GenerateErrorPage,
			HTTPResponse(code, reason),
			NULL,
			""
		);
		return ;
	}
	task->changeJob(
		GetFileContent,
		HTTPResponse(code, reason),
		static_cast<void*>(error_file),
		""
	);
	return ;
}

void VirtualServer::processRequest(HTTPRequest request, Task *task)
{
	std::vector<Location>::iterator it = _locations.begin();
	for (; it != _locations.end(); ++it)
	{
		Path response_path = (*it).checkLocation(request.getPath());
		if (!response_path.empty())
		{
			if (!it->checkAllowedMethods(request.getMethod())) {
				formErrorTask(405, "Method Not Allowed", task);
				return ;
			} else if (request.getMethod() == POST) {
				if (request.bodyLength() > it->getMaxBodySize())
				{
					formErrorTask(413, "Request Entity Too Large", task);
					return ;
				}
				File *file = new File((std::string)response_path, true);
				if (!file->isOpen())
				{
					formErrorTask(500, "Internal Server Error", task);
					return ;
				}
				int code = 200;
				if (file->wasCreated() == true)
					code = 201;
				file->setUriPath(it->getUploadPath(request.getPath()));
				task->changeJob(
					UploadFile,
					HTTPResponse(code, "OK"),
					static_cast<void*>(file),
					request.getBody()
				);
				return ;
			} else if (request.getMethod() == DELETE) {
				File* file = new File((std::string)response_path, false);
				if (!file->isOpen())
				{
					formErrorTask(404, "Not Found", task);
					return ;
				}
				task->changeJob(
					DeleteFile,
					HTTPResponse(200, "OK"),
					static_cast<void*>(file),
					""
				);
				return ;
			} else if (it->autoindex() && (response_path.directory() || Directory::str_is_dir((std::string)response_path))) {
				Directory *directory = new Directory((std::string)response_path);
				task->changeJob(
					GenerateAutoindexPage,
					HTTPResponse(200, "OK"),
					static_cast<void*>(directory),
					(std::string)request.getPath()
				);
				return ;
			} else {
				response_path.addSegment(it->getIndex());
				if (!it->getIndex().empty())
					response_path.setIsDirectory(false);
				File* file = new File((std::string)response_path, false);
				if (!file->isOpen())
				{
					formErrorTask(404, "Not Found", task);
					return ;
				}
				Job job;
				if (request.getMethod() == HEAD)
					job = SendEmptyBody;
				else
					job = GetFileContent;
				task->changeJob(
					job,
					HTTPResponse(200, "OK"),
					static_cast<void*>(file),
					""
				);
				return ;
			}
		}
	}
	formErrorTask(404, "Not Found", task);
	return ;
}
