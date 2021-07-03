/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Task.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 23:57:01 by kdustin           #+#    #+#             */
/*   Updated: 2021/07/02 21:43:40 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TASK_H__
#define __TASK_H__

#include "HTTPResponse.hpp"
#include "HTMLGenerator.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "Utilities.hpp"
#include "ClientSocket.hpp"
#include <poll.h>
#include <vector>
#include <ctime>

enum Job{
	SocketRead,
	SocketWrite,
	ProcessRequest,
	GetFileContent,
	UploadFile,
	DeleteFile,
	GenerateAutoindexPage,
	GenerateErrorPage,
	SendEmptyBody
};

class Task
{
private:
	HTTPResponse 	_response;
	Job				_job;
	void			*_target;
	std::string		_storage;
	ClientSocket	*_socket;

	void deleteContent();

public:
	Task(Job job, HTTPResponse response, void *target, std::string info, ClientSocket *socket);
	Task(const Task&);
	Task& operator=(const Task&);
	~Task();

	bool	contentReady();

	void changeJob(Job job, HTTPResponse response, void *target, std::string info);
	Job job();
	void *getTarget();
	HTTPResponse doJob();

	std::string& getStorage();
	ClientSocket *getSocket();
};

#endif // __TASK_H__
