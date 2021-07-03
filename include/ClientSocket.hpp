#ifndef __CLIENTSOCKET_H__
#define __CLIENTSOCKET_H__

class ClientSocket;

#define SOCKET_BUFFER_SIZE 1024//262144

#include <unistd.h>
#include <poll.h>
#include <iostream>
#include "Signal.hpp"
#include "ConnectionSocket.hpp"

#ifdef DEBUG
std::string tab_message(std::string message);
#endif

class ClientSocket
{
private:
	int					_socket;
	Signal				*_signal;
	char				_buffer[SOCKET_BUFFER_SIZE + 1];

	std::string			_ip;
	size_t				_port;

public:
	ClientSocket();
	ClientSocket(const ClientSocket& other);
	ClientSocket& operator=(const ClientSocket& rhs);

	ClientSocket(int sd, std::string _ip, size_t port);
	~ClientSocket();

	bool readReady();
	bool writeReady();

	bool read(std::string& out);
	bool write(std::string& in);

	Signal	*getSignal();
	int		getSocketDesc();

	std::string getIp();
	size_t getPort();
};

#endif // __CLIENTSOCKET_H__
