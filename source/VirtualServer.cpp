/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:18:43 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 01:18:12 by kdustin          ###   ########.fr       */
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

void VirtualServer::setErrorPage(std::string page) {_error_page = page;}
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

Task VirtualServer::processRequest(HTTPRequest request)
{
	std::vector<Location>::iterator it = _locations.begin();
	for (; it != _locations.end(); ++it)
	{
		Path response_path = (*it).checkLocation(request.getPath());
		if (!response_path.empty())
		{
			if (!(*it).checkAllowedMethods(request.getMethod()))
			{
				///////////////////////////////////////////////////////////////////////////Страницы для разных ошибок
				return (Task(HTTPResponse(405, "Method Not Allowed"), DEFAULT_ERROR));
			}
			if ((*it).getAutoindex())
			{
				Directory dir(response_path.toStr());
				if (!dir.isOpen())
				{
					File error_file(_error_page);
					if (!error_file.isOpen())
						return (Task(HTTPResponse(404, "Not Found"), DEFAULT_ERROR));
					return (Task(HTTPResponse(404, "Not Found"), error_file));
				}
				return (Task(HTTPResponse(200, "OK"), dir));
			}
			else
			{

				File file(response_path.toStr() + (*it).getIndex());
				if (!file.isOpen())
				{
					File error_file(_error_page);
					if (!error_file.isOpen())
						return (Task(HTTPResponse(404, "Not Found"), DEFAULT_ERROR));
					return (Task(HTTPResponse(404, "Not Found"), error_file));
				}
				return (Task(HTTPResponse(200, "OK"), file));
			}
		}
	}
	File error_file(_error_page);
	if (!error_file.isOpen())
		return (Task(HTTPResponse(404, "Not Found"), DEFAULT_ERROR));
	return (Task(HTTPResponse(404, "Not Found"), error_file));
}
