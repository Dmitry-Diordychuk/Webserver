/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directory.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:21:03 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/30 22:17:18 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Directory.hpp"

Directory::Directory() : _dir(NULL), _ent(NULL), _is_open(false) {}

Directory::Directory(std::string path)
{
	_dir = NULL;
	_ent = NULL;
	_is_open = false;
	open(path);
}

Directory::~Directory()
{
	if (_is_open)
		closedir(_dir);
	_is_open = false;
}

void Directory::open(std::string path)
{
	if ((_dir = opendir(path.c_str())) != NULL)
	{
		fcntl(_dir->__dd_fd, F_SETFL, O_NONBLOCK);
		_is_open = true;
		_path = path;
	}
}

std::string Directory::getNextName()
{
	if (_is_open)
	{
		if ((_ent = readdir(_dir)) != NULL)
		{
			if (_ent->d_type == DT_DIR)
			{
				return (std::string(_ent->d_name) + '/');
				_is_dir = true;
			}
			else if (_ent->d_type == DT_REG)
			{
				return (std::string(_ent->d_name));
				_is_dir = false;
			}
		}
	}
	return (std::string(""));
}

bool Directory::isDir()
{
	return (_is_dir);
}

bool Directory::isOpen()
{
	return (_is_open);
}

std::string Directory::getPath()
{
	return (_path);
}

bool Directory::str_is_dir(std::string path)
{
	struct stat path_stat;
	stat(path.c_str(), &path_stat);
	return S_ISDIR(path_stat.st_mode);
}
