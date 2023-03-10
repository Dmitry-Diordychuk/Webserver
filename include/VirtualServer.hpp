/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:17:39 by kdustin           #+#    #+#             */
/*   Updated: 2021/07/02 19:53:57 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_SERVER_HPP
#define VIRTUAL_SERVER_HPP

#include "Location.hpp"
#include "Task.hpp"
#include "HTTPRequest.hpp"
#include <stdexcept>
#include <map>

class VirtualServer
{
private:
	std::string								_server_name;
	std::string								_ip;
	size_t									_port;
	std::map<size_t, std::string>			_error_pages;
	size_t									_client_max_body_size;
	std::vector<Location>					_locations;

	VirtualServer();
public:
	VirtualServer(std::string server_name, std::string ip, size_t port);
	~VirtualServer();

	void addErrorPage(int code, std::string path);
	void setMaxBodySize(size_t size);
	std::string	getServerName();
	std::string getIp();
	size_t		getPort();

	void addLocation(Location location);

	void formErrorTask(size_t code, std::string reason, Task *task);
	void processRequest(HTTPRequest request, Task *task);
};




#endif // VIRTUAL_SERVER_HPP
