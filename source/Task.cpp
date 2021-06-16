/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Task.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 00:07:22 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 17:40:13 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Task.hpp"

Task::Task() {}
Task::~Task() {}

int Task::getFD()
{
	return (_fd);
}

Task::Task(const Task& other)
{
	_fd = other._fd;
	_response = other._response;
	_todo = other._todo;
	_file = other._file;
	_dir = other._dir;
}

Task& Task::operator=(const Task& rhs)
{
	if (this == &rhs)
		return (*this);
	_fd = rhs._fd;
	_response = rhs._response;
	_todo = rhs._todo;
	_file = rhs._file;
	_dir = rhs._dir;
	return (*this);
}

Task::Task(HTTPResponse response, ToDo todo) {
	_response = response;
	_todo = todo;
	_fd = -1;
}

Task::Task(HTTPResponse response, File file)
{
	_response = response;
	_todo = GET_FILE_CONTENT;
	_fd = file.getFD();
}

Task::Task(HTTPResponse response, Directory dir)
{
	_response = response;
	_todo = AUTOINDEX;
	_fd = dir.getFD();
}

HTTPResponse Task::getHTTPMessage()
{
	return (_response);
}

ToDo Task::getTodo()
{
	return (_todo);
}

File Task::getFile()
{
	return (_file);
}

Directory Task::getDir()
{
	return (_dir);
}

HTTPResponse Task::doJob()
{
	if (_todo == GET_FILE_CONTENT)
		_response.setBody(_file.getContent());
	// else if (task.getTodo() == AUTOINDEX)
	// 	response.setBody(task.getDir() // АВТОИНДЕКС
	// else if (task.getTodo() == DEFAULT_ERROR)
	// 	response.setBody()           // Ошибка генерировать
	return (_response);
}
