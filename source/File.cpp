/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 01:37:30 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 02:49:08 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"

File::File(){}

File::File(std::string path)
	: _buffer(256)
{
	char_type *start = &_buffer.front();
	char_type *end = start + _buffer.size();
	setg(start, end, end);
	openFile(path);
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

bool File::openFile(std::string path)
{
	struct stat buff;
	stat(path.c_str(), &buff);
	if (S_ISDIR(buff.st_mode))
		return (_is_open = false);
	if ((_fd = open(path.c_str(), O_RDONLY)) < 0)
		return (_is_open = false);
	else
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
	if (_is_open)
	{
		std::istream in(this);


		while (std::getline(in, line))
			line += line;
	}
	return (line);
}
