/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 01:37:30 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/22 18:18:36 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"

File::File(){}

File::File(std::string path, bool read)
	: _buffer(256)
{
	char_type *start = &_buffer.front();
	char_type *end = start + _buffer.size();
	setg(start, end, end);
	openFile(path, read);
}

File::~File()
{
	closeFile();
}

int File::underflow()
{
	if (!_is_open)
		return traits_type::eof();
	if (gptr() < egptr())
		return (*gptr());
	char_type *start = eback();
	size_t rd = read(_fd, start, _buffer.size());
	setg(start, start, start + rd);
	return (rd > 0 ? *gptr() : traits_type::eof());
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
	//fcntl(_fd, F_SETFL, O_NONBLOCK); //сбрасывает O_APPEND?
	_type = "text/" + path.substr(path.find_last_of(".") + 1);
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
	std::string line;
	std::string result;
	if (_is_open)
	{
		std::istream in(this);

		while (std::getline(in, line))
			result += line;
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
