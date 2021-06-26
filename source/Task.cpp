/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Task.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 00:07:22 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/23 15:36:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Task.hpp"

Task::Task() {}

Task::Task(Job job, size_t socket)
{
	_dir = NULL;
	_file = NULL;

	_job = job;
	_pollfd.fd = socket;
	_pollfd.events = POLLIN;
	_pollfd.revents = 1;
}

Task::Task(Job job, size_t socket, size_t server_index)
{
	_dir = NULL;
	_file = NULL;

	_job = job;
	_pollfd.fd = socket;
	_pollfd.events = POLLIN;
	_pollfd.revents = 1;
	_vserv_index = server_index;
}

Task::Task(const Task& other)
{
	_return_fd = other._return_fd;
	_response = other._response;
	_job = other._job;
	_file = other._file;
	_dir = other._dir;
	_vserv_index = other._vserv_index;
}

Task& Task::operator=(const Task& rhs)
{
	if (this == &rhs)
		return (*this);
	_return_fd = rhs._return_fd;
	_response = rhs._response;
	_job = rhs._job;
	_file = rhs._file;
	_dir = rhs._dir;
	_vserv_index = rhs._vserv_index;
	return (*this);
}

Task::~Task() {
	delete _dir;
	delete _file;
}

// void Task::pollJobs(std::vector<Task*> tasks)
// {
// 	// std::vector<Task*>::iterator it = tasks.begin();
// 	// for (; it != tasks.end(); ++it)
// 	// {
// 	// 	pollfd* pollfd = &(*it)->_pollfd;
// 	// 	if ( < 0)
// 	// 		throw std::runtime_error(std::string(strerror(errno)));
// 	// }
// }

bool Task::readyToRead()
{
	if (_pollfd.revents & POLLIN)
	{
		_pollfd.revents &= ~POLLIN;
		return (true);
	}
	return (false);
}

bool Task::readyToWrite()
{
	if (_pollfd.revents & POLLOUT)
	{
		_pollfd.revents &= ~POLLOUT;
		return (true);
	}
	return (false);
}

int Task::getFD()
{
	return (_pollfd.fd);
}

int Task::returnFD()
{
	return (_return_fd.fd);
}

size_t Task::getVServIndex()
{
	return (_vserv_index);
}

Job Task::job()
{
	return (_job);
}

void Task::changeJob(Job new_job, HTTPResponse message)
{
	_response = message;
	_job = new_job;
}

void Task::changeJob(Job new_job, File *file, HTTPResponse message)
{
	_file = file;
	_job = new_job;
	_response = message;
	_return_fd = _pollfd;
	_pollfd.fd = _file->getFD();
	_pollfd.events = POLLIN;
	_pollfd.revents = 1;
}

void Task::changeJob(Job new_job, Directory *dir, HTTPResponse message)
{
	_job = new_job;
	_dir = dir;
	_job = AUTOINDEX;
	_response = message;
}

void Task::changeJob(Job new_job, File *file, std::string servpath, std::string content, HTTPResponse message)
{
	_job = new_job;
	_file = file;
	_storage = content;
	_response = message;
	_return_fd = _pollfd;
	_pollfd.fd = _file->getFD();
	_pollfd.events = POLLOUT;
	_pollfd.revents = 1;
	_server_path = servpath;
}

std::string getCurrentTime()
{
	char mbstr[100];
	std::time_t t = std::time(NULL);
	std::strftime(mbstr, sizeof(mbstr), "%a, %d %b %Y %H:%M:%S GMT", std::gmtime(&t));
	return (std::string(mbstr));
}

HTTPResponse Task::doJob()
{
	_response.addField("Server", "42Webserv");
	_response.addField("Date", getCurrentTime());
	if (_job == GET_FILE_CONTENT || _job == EMPTY_BODY)
	{
		_response.addField("Last-Modified", _file->getLastModTime());
		if (_job == GET_FILE_CONTENT)
			_response.setBody(_file->getContent());
		else if (_job == EMPTY_BODY)
			_response.addField("Content-Length", intToStr(_file->getContent().length()));
		_response.addField("Content-Type", _file->getType());
		_response.addField("Connection", "Closed");
	}
	else if (_job == AUTOINDEX)
	{
		_response.addField("Last-Modified", getCurrentTime());
	 	_response.setBody(HTMLGenerator::Autoindex(_dir));
		_response.addField("Content-Type", "text/html");
		_response.addField("Connection", "Closed");
	}
	else if (_job == UPLOAD)
	{
		_file->writeToFile(_storage);
		_response.addField("Location", _server_path);
	}
	else if (_job == DELETE_FILE)
		_file->deleteFile();
	else if (_job == GENERATE_ERROR_PAGE)
	{
		_response.addField("Last-Modified", getCurrentTime());
	 	_response.setBody("<h1>" + intToStr(_response.getCode()) + " " + _response.getReason()  + "</h1>");
		_response.addField("Content-Type", "text/html");
		_response.addField("Connection", "Closed");
	}
	return (_response);
}

pollfd& Task::getPollfd()
{
	return (_pollfd);
}
