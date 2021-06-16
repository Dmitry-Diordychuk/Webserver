/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Desc.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 23:13:19 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 17:39:34 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Desc.hpp"

Desc::Desc(){}
Desc::~Desc(){}

bool Desc::readyToRead(size_t index)
{
	if (_descriptors[index].revents & POLLIN)
	{
		_descriptors[index].revents &= ~POLLIN;
		return (true);
	}
	return (false);
}

bool Desc::readyToWrite(size_t index)
{
	if (_descriptors[index].revents & POLLOUT)
	{
		_descriptors[index].revents &= ~POLLOUT;
		return (true);
	}
	return (false);
}

int Desc::getFD(size_t index)
{
	return (_descriptors[index].fd);
}

Type Desc::getType(size_t index)
{
	return (_type[index]);
}

Task Desc::getTask(size_t index)
{
	return (_tasks[index]);
}

pollfd* Desc::getPollfdSet()
{
	return (&_descriptors.front());
}

void Desc::addDesc(int fd, Type type)
{
	pollfd fd_state;
	fd_state.fd = fd;
	fd_state.events = POLLIN;
	fd_state.revents = 0;
	_descriptors.push_back(fd_state);
	_type.push_back(type);
}

void Desc::addDesc(Task task)
{
	pollfd fd_state;
	fd_state.fd = task.getFD();
	fd_state.events = 0;
	fd_state.revents = 1;
	_descriptors.push_back(fd_state);
	_type.push_back(TASK);
}

void Desc::delDesc(size_t index)
{
	_descriptors.erase(_descriptors.begin() + index);
	_type.erase(_type.begin() + index);
	_tasks.erase(_tasks.begin() + index);
}

size_t Desc::size()
{
	return (_descriptors.size());
}
