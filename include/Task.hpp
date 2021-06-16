/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Task.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 23:57:01 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 17:32:45 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TASK_H__
#define __TASK_H__

#include "HTTPResponse.hpp"
#include "Directory.hpp"
#include "File.hpp"

enum ToDo{
	GET_FILE_CONTENT,
	AUTOINDEX,
	DEFAULT_ERROR
};

class Task
{
private:
	HTTPResponse 	_response;
	ToDo			_todo;
	File			_file;
	Directory		_dir;
	int				_fd;

public:
	Task();
	Task(const Task&);
	Task& operator=(const Task&);
	Task(HTTPResponse response, ToDo todo);
	Task(HTTPResponse response, File file);
	Task(HTTPResponse response, Directory dir);
	~Task();

	int getFD();
	HTTPResponse getHTTPMessage();
	ToDo getTodo();
	File getFile();
	Directory getDir();

	HTTPResponse doJob();
};

#endif // __TASK_H__
