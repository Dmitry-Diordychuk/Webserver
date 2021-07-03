/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionSocket.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:17:48 by kdustin           #+#    #+#             */
/*   Updated: 2021/07/02 11:59:25 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionSocket.hpp"

/*
	{
	timeval tv;
	tv.tv_sec = static_cast<long>(read_timeout_sec_);
	tv.tv_usec = static_cast<decltype(tv.tv_usec)>(read_timeout_usec_);
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));
	}
	{
	timeval tv;
	tv.tv_sec = static_cast<long>(write_timeout_sec_);
	tv.tv_usec = static_cast<decltype(tv.tv_usec)>(write_timeout_usec_);
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv));
	}
*/

ConnectionSocket::ConnectionSocket() {
	_signal = new Signal();
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("Create: " + std::string(strerror(errno)));
#ifdef DEBUG
	int opt = 1;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
	std::cout << "Server SD: " << _socket << std::endl;
#endif
	fcntl(_socket, F_SETFL, O_NONBLOCK);
}

ConnectionSocket::~ConnectionSocket() {
	if (close(_socket) < 0)
		throw std::runtime_error("Close: " + std::string(strerror(errno)));
#ifdef DEBUG
	std::cout << "Socket " << _socket << " has been closed" << std::endl;
#endif
	delete _signal;
}

int callCListen(int sd)
{
	return (listen(sd, MAX_CONNECTIONS));
}

void ConnectionSocket::listen(std::string ip, size_t port)
{
	_ip = ip;
	_port = port;
	struct sockaddr_in socket_address_in;
	socket_address_in.sin_family = AF_INET;
	socket_address_in.sin_addr.s_addr = inet_addr(ip.c_str());
	if (socket_address_in.sin_addr.s_addr == INADDR_NONE)
		throw std::runtime_error("Bind:" + std::string(strerror(errno)));
	socket_address_in.sin_port = htons(port);

	size_t address_size = sizeof(socket_address_in);
	if (bind(_socket, (struct sockaddr *)&socket_address_in, address_size) < 0)
		throw std::runtime_error("Bind:" + std::string(strerror(errno)));
#ifdef DEBUG
	std::cout << "Server " << _socket << " has been binded" << std::endl;
#endif

	// Указывает что сокет используется для приема соединения.
	if (callCListen(_socket) < 0)
		throw std::runtime_error("Listen: " + std::string(strerror(errno)));
#ifdef DEBUG
	std::cout << "Server " << _socket << " is listening" << std::endl;
#endif
}

int callCAccept(int sd)
{
	struct sockaddr_in	new_address_in;
	int new_socket = accept(
							sd,
							(struct sockaddr *)&new_address_in,
							(socklen_t*)&new_address_in
							);
	return (new_socket);
}

ClientSocket *ConnectionSocket::accept()
{
	// Возвращает дескпритор сокета, соединенного с клиентом, вызвашим функцию connect.
	// Функция accept блокирующая до тех пор пока не поступит хоть один запрос.
	// Poll испльзуеться для избежания блокировки.
	if (!_signal->readReady())
		return (NULL);
	int new_socket = callCAccept(_socket);
	if (new_socket < 0)
		throw std::runtime_error("Accept: " + std::string(strerror(errno)));
	fcntl(new_socket, F_SETFL, O_NONBLOCK);
#ifdef DEBUG
	std::cout << "Server " << _socket << " has accepted new conection SD: " << new_socket << std::endl;
#endif
	return (new ClientSocket(new_socket, _ip, _port));
}

int ConnectionSocket::getSocketDesc()
{
	return (_socket);
}

Signal* ConnectionSocket::getSignal() {
	return (_signal);
}

// std::string ConnectionSocket::reciveMessage(int sd)
// {
// 	// Функция recv тоже блокирующая
// 	char buffer[MAX_HTTP] = {0};
// 	recv(sd, buffer, MAX_HTTP, MSG_PEEK);
// #ifdef DEBUG
// 	std::cout << "Message from SD: " << sd << "\n" << tab_message(std::string(buffer)) << std::endl;
// #endif
// 	return (std::string(buffer));
// }

// void ConnectionSocket::sendMessage(int sd, std::string message)
// {
// #ifdef DEBUG
// 	std::cout << "Send message to SD: " << sd << "\n" << tab_message(message) << std::endl;
// 	int state = send(sd, message.c_str(), message.length(), 0);
// 	if (state < 0)
// 		std::cout << "Send error: " << strerror(errno) << std::endl;
// #else
// 	send(sd, message.c_str(), message.length(), 0);
// #endif
// }
