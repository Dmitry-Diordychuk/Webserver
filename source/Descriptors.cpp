#include "Descriptors.hpp"

int callCPoll(pollfd *pfd, size_t n, int timeout)
{
	return (poll(pfd, n, timeout));
}

Descriptors::Descriptors()
{
}

Descriptors::~Descriptors()
{
}

void Descriptors::add(ConnectionSocket *socket) {
	pollfd pfd;
	pfd.fd = socket->getSocketDesc();
	pfd.events = POLLIN;
	pfd.revents = 0;
	_pollfds.push_back(pfd);
	_signals.push_back(socket->getSignal());
}

void Descriptors::add(ClientSocket *socket) {
	pollfd pfd;
	pfd.fd = socket->getSocketDesc();
	pfd.events = (POLLIN|POLLOUT);
	pfd.revents = 0;
	_pollfds.push_back(pfd);
	_signals.push_back(socket->getSignal());
}

void Descriptors::add(Task *task) {
	if (task->job() == GetFileContent
		|| task->job() == SendEmptyBody
		|| task->job() == UploadFile
		|| task->job() == DeleteFile
	) {
		File *file = static_cast<File*>(task->getTarget());
		pollfd pfd;
		pfd.fd = file->getFD();
		pfd.events = (POLLIN|POLLOUT);
		pfd.revents = 0;
		_pollfds.push_back(pfd);
		_signals.push_back(file->getSignal());
	}
}
void Descriptors::poll()
{
	// Delete NULL pointers and fds associated with them
	std::vector<Signal*>::iterator sig_it = _signals.begin();
	std::vector<pollfd>::iterator pol_it = _pollfds.begin();
	for (; sig_it != _signals.end(); ++sig_it, ++pol_it)
	{
		if (*sig_it == NULL)
		{
			_signals.erase(sig_it);
			_pollfds.erase(pol_it);
		}
	}

	callCPoll(&_pollfds.front(), _pollfds.size(), POLL_TIMEOUT);
	for (size_t i = 0; i < _pollfds.size(); ++i)
	{
		if (_pollfds[i].revents & POLLIN)
		{
			_pollfds[i].revents &= ~POLLIN;
			_signals[i]->setRead(true);
		}
		if (_pollfds[i].revents & POLLOUT)
		{
			_pollfds[i].revents &= ~POLLOUT;
			_signals[i]->setWrite(true);
		}
	}
}
