/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 01:37:30 by kdustin           #+#    #+#             */
/*   Updated: 2021/07/02 23:47:03 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"

File::File(){}

File::File(std::string path, bool read)
{
	openFile(path, read);
	_signal = new Signal();
}

File::~File()
{
	closeFile();
	delete _signal;
	_signal = NULL;
}

bool File::openFile(std::string path, bool read)
{
	_path = path;
	struct stat buff;
	if (read == false)
	{
		stat(path.c_str(), &buff);
		if (S_ISDIR(buff.st_mode))
			return (_is_open = false);
		if ((_fd = open(path.c_str(), O_RDONLY)) < 0)
			return (_is_open = false);
	}
	else
	{
		_was_created = false;
		if ((_fd = open(path.c_str(), O_WRONLY | O_APPEND)) < 0)
		{
#ifdef DEBUG
			std::cout << "Open file for writing error" << std::endl;
			std::cout << strerror(errno) << std::endl;
#endif // !DEBUG
			_was_created = true;
			if ((_fd = open(path.c_str(), O_WRONLY | O_CREAT, 0644)) < 0)
			{
#ifdef DEBUG
				std::cout << "Create file error" << std::endl;
				std::cout << strerror(errno) << std::endl;
#endif // !DEBUG
				return (_is_open = false);
			}
		}
		stat(path.c_str(), &buff);
	}
	char mbstr[100];
	std::time_t mod_t = buff.st_mtime;
	std::strftime(mbstr, sizeof(mbstr), "%a, %d %b %Y %H:%M:%S GMT", std::gmtime(&mod_t));
	_last_mod_time = std::string(mbstr);
	//fcntl(_fd, F_SETFL, O_NONBLOCK); //???????????????????? O_APPEND?
	std::string extension = path.substr(path.find_last_of(".") + 1);
	if (extension == "html")
		_type = "text/" + extension;
	else if (extension == "gif")
		_type = "image/" + extension;
	return (_is_open = true);
}

void File::closeFile()
{
	if (_is_open)
		close(_fd);
}

bool File::isOpen()
{
	return (_is_open);
}

int File::getFD()
{
	return (_fd);
}

std::string File::getContent()
{
	std::string result;
	if (_is_open)
	{
		FDBuffer buff(_fd);
		std::istream in(&buff);

		char c;
		while (in.get(c))
			result += c;
	}
	return (result);
}

void File::writeToFile(std::string content)
{
	if (_is_open)
		write(_fd, content.c_str(), content.length());
}

void File::deleteFile()
{
	if (_is_open)
		closeFile();
	remove(_path.c_str());
}

std::string File::getType()
{
	return (_type);
}

std::string File::getLastModTime()
{
	return (_last_mod_time);
}

bool File::wasCreated()
{
	return (_was_created);
}

bool File::readReady() {
	return (_signal->readReady());
}

bool File::writeReady() {
	return (_signal->writeReady());
}

Signal* File::getSignal() {
	return (_signal);
}

void File::setUriPath(std::string uri_path)
{
	_uri_path = uri_path;
}

std::string File::getUriPath()
{
	return (_uri_path);
}
