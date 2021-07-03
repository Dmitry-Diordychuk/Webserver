#include "ClientSocket.hpp"

#ifdef DEBUG
std::string tab_message(std::string message)
{
	message = "\t" + message;
	size_t index = 0;
	while ((index = message.find("\n", index)) != std::string::npos)
	{
		++index;
		message.insert(index, "\t");
	}
	return (message);
}
#endif

ClientSocket::ClientSocket() {}

ClientSocket::ClientSocket(const ClientSocket& other) {
	_socket = other._socket;
	_signal = other._signal;
	_ip = other._ip;
	_port = other._port;
}

ClientSocket& ClientSocket::operator=(const ClientSocket& rhs) {
	if (this == &rhs)
		return (*this);
	_socket = rhs._socket;
	_signal = rhs._signal;
	_ip = rhs._ip;
	_port = rhs._port;
	return (*this);
}

ClientSocket::ClientSocket(int sd, std::string ip, size_t port)
	: _socket(sd), _ip(ip), _port(port)
{
	_signal = new Signal();
}

ClientSocket::~ClientSocket()
{
	delete _signal;
	_signal = NULL;
	if (close(_socket) < 0)
		throw std::runtime_error("Close: " + std::string(strerror(errno)));
#ifdef DEBUG
	std::cout << "Socket " << _socket << " has been closed" << std::endl;
#endif
}

bool ClientSocket::readReady() {
	if (_signal->readReady())
		return (true);
	return (false);
}
bool ClientSocket::writeReady() {
	if (_signal->writeReady())
		return (true);
	return (false);
}

bool ClientSocket::read(std::string& out) {
	memset(_buffer, 0, SOCKET_BUFFER_SIZE + 1);
	recv(_socket, _buffer, SOCKET_BUFFER_SIZE, 0);
	_buffer[SOCKET_BUFFER_SIZE] = '\0';
	std::string str(_buffer);
#ifdef DEBUG
	std::cout << "Message from SD: " << _socket << "\n" << tab_message(str) << std::endl;
#endif

	out += str;
	if (str.length() == SOCKET_BUFFER_SIZE)
		return (false);
	return (true);
}

bool ClientSocket::write(std::string& in) {
	std::string part = in.substr(0, SOCKET_BUFFER_SIZE);
	if (in.length() == SOCKET_BUFFER_SIZE)
		in = in.substr(SOCKET_BUFFER_SIZE);
#ifdef DEBUG
	std::cout << "Send message to SD: " << _socket << "\n" << tab_message(part) << std::endl;
#endif
	send(_socket, part.c_str(), part.length(), 0);

	if (part.length() == SOCKET_BUFFER_SIZE)
		return (false);
	return (true);
}

Signal* ClientSocket::getSignal() {
	return (_signal);
}

int		ClientSocket::getSocketDesc() {
	return (_socket);
}

std::string ClientSocket::getIp() {
	return (_ip);
}

size_t ClientSocket::getPort() {
	return (_port);
}
