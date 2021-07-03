/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:41:17 by kdustin           #+#    #+#             */
/*   Updated: 2021/07/02 00:24:04 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include "VirtualServer.hpp"
#include "ClientSocket.hpp"
#include <string>
#include <vector>

class Config
{
private:
	std::vector<std::vector<VirtualServer> >	_virservers;
	size_t										_max_sockets;
	size_t										_socket_timeout;

public:
	void addVirtualServer(VirtualServer virtserv);
	void setMaxSockets(size_t max_sockets);
	void socketTimeout(size_t soket_timeout);

	VirtualServer* getVirtualServer(ClientSocket *socket, std::string host_server_name);
	std::string getIpAt(size_t index);
	size_t getPortAt(size_t index);
	size_t size();

	size_t getMaxSockets();
	size_t getSocketTimeout();
};

#endif // __CONFIG_HPP__
