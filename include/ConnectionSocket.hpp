/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionSocket.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:00:00 by kdustin           #+#    #+#             */
/*   Updated: 2021/07/02 09:51:59 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ConnectionSocket_HPP
#define ConnectionSocket_HPP

class ConnectionSocket;

#include <stdexcept>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string>
#include "ClientSocket.hpp"
#include "Signal.hpp"

#define MAX_CONNECTIONS 1000000

#ifdef DEBUG
#include <iostream>
#endif

int callCListen(int sd);
int callCAccept(int sd);

class ConnectionSocket
{
private:
	int		_socket;
	Signal	*_signal;

	std::string	_ip;
	size_t		_port;

public:
	ConnectionSocket();
	~ConnectionSocket();

	void listen(std::string ip, size_t port);
	ClientSocket *accept();

	int		getSocketDesc();
	Signal	*getSignal();
}; // class ConnectionSocket

#endif // ConnectionSocket_HPP
