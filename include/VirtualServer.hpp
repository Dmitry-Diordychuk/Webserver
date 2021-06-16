/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualServer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:17:39 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 16:53:13 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_SERVER_HPP
#define VIRTUAL_SERVER_HPP

#include "Location.hpp"
#include "Task.hpp"
#include "HTTPRequest.hpp"
#include <stdexcept>

class VirtualServer
{
private:
	std::string				_server_name;
	std::string				_ip;
	size_t					_port;
	std::string				_error_page;
	size_t					_client_max_body_size;
	std::vector<Location>	_locations;

	VirtualServer();
public:
	VirtualServer(std::string server_name, std::string ip, size_t port);
	~VirtualServer();

	void setErrorPage(std::string page);
	void setMaxBodySize(size_t size);
	std::string	getServerName();
	std::string getIp();
	size_t		getPort();

	void addLocation(Location location);

	Task processRequest(HTTPRequest request);
};




#endif // VIRTUAL_SERVER_HPP
