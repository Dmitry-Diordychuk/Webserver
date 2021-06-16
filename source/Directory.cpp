/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directory.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:21:03 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 17:37:38 by kdustin          ###   ########.fr       */
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
		_is_open = true;
}

std::string Directory::getNextName()
{
	if (_is_open)
	{
		if ((_ent = readdir(_dir)) != NULL)
		{
			if (_ent->d_type == DT_DIR)
				return (std::string(_ent->d_name) + '/');
			else if (_ent->d_type == DT_REG)
				return (std::string(_ent->d_name));
		}
	}
	return (std::string(""));
}

bool Directory::isOpen()
{
	return (_is_open);
}

int Directory::getFD()
{
	return (_dir->__dd_fd);
}
