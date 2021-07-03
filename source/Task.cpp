/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Task.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 00:07:22 by kdustin           #+#    #+#             */
/*   Updated: 2021/07/02 23:48:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Task.hpp"

Task::Task(Job job, HTTPResponse response, void *target, std::string info, ClientSocket *socket) {
	_job = job;
	_response = response;
	_target = target;
	_storage = info;
	_socket = socket;
}

void Task::deleteContent()
{
	if (_job == GetFileContent || _job == UploadFile || _job == DeleteFile || _job == SendEmptyBody)
	{
		File *file = static_cast<File*>(_target);
		delete file;
		_target = NULL;
	}
	else if (_job == GenerateAutoindexPage)
	{
		Directory *directory = static_cast<Directory*>(_target);
		delete directory;
		_target = NULL;
	}
}

Task::~Task() {
#ifdef DEBUG
	std::cout << "Task deleted" << std::endl;
#endif
	delete _socket;
	deleteContent();
}

Job Task::job()
{
	return (_job);
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
	if (_job == GetFileContent || _job == SendEmptyBody)
	{
		_response.addField("Server", "42Webserv");
		_response.addField("Date", getCurrentTime());
		File *file = static_cast<File*>(_target);
		_response.addField("Last-Modified", file->getLastModTime());
		if (_job == GetFileContent)
			_response.setBody(file->getContent());
		else if (_job == SendEmptyBody)
			_response.addField("Content-Length", convertNumtoStr(_response.bodyLength()));
		_response.addField("Content-Type", file->getType());
		_response.addField("Connection", "Closed");
	}
	else if (_job == GenerateAutoindexPage)
	{
		_response.addField("Server", "42Webserv");
		_response.addField("Date", getCurrentTime());
		Directory *directory = static_cast<Directory*>(_target);
		_response.addField("Last-Modified", getCurrentTime());
	 	_response.setBody(HTMLGenerator::Autoindex(directory, _storage));
		_response.addField("Content-Type", "text/html");
		_response.addField("Connection", "Closed");
	}
	else if (_job == UploadFile)
	{
		_response.addField("Server", "42Webserv");
		_response.addField("Date", getCurrentTime());
		File *file = static_cast<File*>(_target);
		file->writeToFile(_storage);
		_response.addField("Location", file->getUriPath());
	}
	else if (_job == DeleteFile)
	{
		_response.addField("Server", "42Webserv");
		_response.addField("Date", getCurrentTime());
		File *file = static_cast<File*>(_target);
		file->deleteFile();
	}
	else if (_job == GenerateErrorPage)
	{
		_response.addField("Server", "42Webserv");
		_response.addField("Date", getCurrentTime());
		_response.addField("Last-Modified", getCurrentTime());
	 	_response.setBody("<h1>" + convertNumtoStr(_response.getCode()) + " " + _response.getReason()  + "</h1>");
		_response.addField("Content-Type", "text/html");
		_response.addField("Connection", "Closed");
	}
	return (_response);
}

std::string& Task::getStorage()
{
	return (_storage);
}

ClientSocket* Task::getSocket() {
	return (_socket);
}

bool	Task::contentReady() {
	if (_job == SocketRead) {
		return (_socket->readReady());
	} else if (_job == SocketWrite) {
		return (_socket->writeReady());
	} else if (_job == GetFileContent || _job == SendEmptyBody) {
		File *file = static_cast<File*>(_target);
		return (file->readReady());
	} else if (_job == UploadFile || _job == DeleteFile) {
		File *file = static_cast<File*>(_target);
		return (file->writeReady());
	}
	return (true);
}

void Task::changeJob(Job job, HTTPResponse response, void *target, std::string info)
{
	if (_target != NULL)
		deleteContent();
	_job = job;
	_response = response;
	_target = target;
	_storage = info;
}

void* Task::getTarget() {
	return (_target);
}
