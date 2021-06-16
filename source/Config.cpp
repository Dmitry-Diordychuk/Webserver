/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 02:04:04 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/15 03:00:10 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

void Config::addVirtualServer(VirtualServer virtserv)
{
	if (!_virservers.empty())
	{
		std::vector<std::vector<VirtualServer> >::iterator it = _virservers.begin();
		for (; it != _virservers.end(); ++it)
		{
			if ((*it)[0].getIp() == virtserv.getIp() && (*it)[0].getPort() == virtserv.getPort())
			{
				(*it).push_back(virtserv);
				return ;
			}
		}
	}
	std::vector<VirtualServer> ip_col;
	_virservers.push_back(ip_col);
	_virservers.back().push_back(virtserv);
}

void Config::setMaxSockets(size_t max_sockets)
{
	_max_sockets = max_sockets;
}

void Config::socketTimeout(size_t soket_timeout)
{
	_socket_timeout = soket_timeout;
}

std::string Config::getIpAt(size_t index)
{
	return (_virservers.at(index)[0].getIp());
}

size_t Config::getPortAt(size_t index)
{
	return (_virservers.at(index)[0].getPort());
}

size_t Config::size()
{
	return (_virservers.size());
}

size_t Config::getMaxSockets()
{
	return (_max_sockets);
}

size_t Config::getSocketTimeout()
{
	return (_socket_timeout);
}

VirtualServer Config::getVirtualServerAt(size_t index, std::string host_server_name)
{
	if (host_server_name.empty())
		return (*_virservers.at(index).begin());
	std::vector<VirtualServer> servers_list = _virservers.at(index);
	std::vector<VirtualServer>::iterator it = servers_list.begin();
	for (; it != servers_list.end(); ++it)
	{
		if ((*it).getServerName() == host_server_name)
			return (*it);
	}
	return (*servers_list.begin());
}
