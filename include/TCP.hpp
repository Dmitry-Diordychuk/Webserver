/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:00:00 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/10 16:35:37 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_HPP
#define TCP_HPP

#include <sstream>
#include <stdexcept>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

#ifdef DEBUG
#include <iostream>
#endif

class TCP
{
private:
	TCP();
	~TCP();
public:

	static int createConnectionSocket();
	static void bindConnectionSocket(int sd, std::string ip, size_t port);
	static void startListen(int sd, size_t max_connections);
	static int acceptConnection(int sd);
	static void closeConnection(int sd);

	static std::string reciveMessage(int sd);
	static void sendMessage(int sd, std::string message);
}; // class TCP

#endif // TCP_HPP
