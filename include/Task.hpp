/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Task.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 23:57:01 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/27 00:52:21 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TASK_H__
#define __TASK_H__

#include "HTTPResponse.hpp"
#include "HTMLGenerator.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include <poll.h>
#include <vector>
#include <ctime>
#include "Utilities.hpp"

enum Job{
	LISTEN,
	RECEIVE_REQUEST,
	GET_FILE_CONTENT,
	AUTOINDEX,
	GENERATE_ERROR_PAGE,
	EMPTY_BODY,
	UPLOAD,
	DELETE_FILE
};

class Task
{
private:
	HTTPResponse 	_response;
	Job				_job;
	File			*_file;
	Directory		*_dir;
	size_t			_vserv_index;
	pollfd			_pollfd;
	pollfd			_return_fd;

	//Upload
	std::string		_storage;
	std::string		_server_path;

public:
	Task();
	Task(Job job, size_t socket);
	Task(Job job, size_t socket, size_t server_index);
	Task(const Task&);
	Task& operator=(const Task&);
	~Task();

	//static void pollJobs(std::vector<Task*> tasks);

	bool	readyToRead();
	bool	readyToWrite();

	int		getFD();
	int		returnFD();
	size_t	getVServIndex();

	Job job();
	void changeJob(Job new_job, HTTPResponse message);
	void changeJob(Job new_job, File *file, HTTPResponse message);
	void changeJob(Job new_job, Directory *dir, std::string uri, HTTPResponse message);
	void changeJob(Job new_job, File *file, std::string servpath, std::string content, HTTPResponse message);
	HTTPResponse doJob();

	pollfd& getPollfd();
};

#endif // __TASK_H__
