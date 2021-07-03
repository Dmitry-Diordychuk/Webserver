#ifndef __DESCRIPTORS_H__
#define __DESCRIPTORS_H__

#include "ClientSocket.hpp"
#include "ConnectionSocket.hpp"
#include "Signal.hpp"
#include "Task.hpp"
#include <poll.h>
#include <vector>

#define POLL_TIMEOUT 1

int callCPoll(pollfd *pfd, size_t n, int timeout);

class Descriptors
{
private:
	std::vector<pollfd> _pollfds;
	std::vector<Signal*> _signals;

public:
	Descriptors();
	~Descriptors();

	void add(ConnectionSocket *socket);
	void add(ClientSocket *socket);
	void add(Task *task);

	void poll();
};

#endif // __DESCRIPTORS_H__
