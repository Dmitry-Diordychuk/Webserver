/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:52:15 by kdustin           #+#    #+#             */
/*   Updated: 2021/07/01 09:11:13 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {}

Server::Server(Config conf)
	:	_config(conf)
{}

Server::~Server() {}

void Server::start()
{
	try
	{
		std::vector<Task*> tasks;
		// Инициализация сокетов
		for (size_t i = 0; i < _config.size(); ++i)
		{
			int server_sd = TCP::createConnectionSocket();
			TCP::bindConnectionSocket(server_sd, _config.getIpAt(i), _config.getPortAt(i));
			TCP::startListen(server_sd, _config.getMaxSockets());
			tasks.push_back(new Task(LISTEN, server_sd));
		}

		// Основной цикл
		while (1)
		{
			// Для каждого набора серверных сокетов.
			for (size_t i = 0; i < tasks.size(); ++i)
			{
				poll(&tasks[i]->getPollfd(), 1, 1);
				if (tasks[i]->readyToRead() || tasks[i]->readyToWrite())
				{
					if (tasks[i]->job() == LISTEN)
					{
						// Устанавливает TCP соединение.
						int new_socket = TCP::acceptConnection(tasks[i]->getFD());
						tasks.push_back(new Task(RECEIVE_REQUEST, new_socket, i));
					}
					else if (tasks[i]->job() == RECEIVE_REQUEST)
					{
						// Принимает запрос
						std::stringstream message;
						message << TCP::reciveMessage(tasks[i]->getFD());

						HTTPRequest request(8000);
						try
						{
							// Парсинг запроса
							request.parseRequest(message);

							if (request.isChunked())
							{
								ChunkedBody chunked_body;
								chunked_body.decode(request.getBody());
								while (chunked_body.getState() != Complete && chunked_body.getState() != Error)
								{
									std::stringstream chunk;
									chunk << TCP::reciveMessage(tasks[i]->getFD());
									chunked_body.decode(chunk.str());
								}
								if (chunked_body.getState() == Complete)
								{
									request.setBody((std::string)chunked_body);
									request.changeChunkedToLength();
								}
								else
									HTTPException(BAD_REQUEST_ERROR);
							}

							// Обработать запрос и сформировать задачу
							_config.getVirtualServerAt(tasks[i]->getVServIndex(),
														request.getHostField()).processRequest(request, tasks[i]);
						}
						catch(const HTTPException& e)
						{
							_config.getVirtualServerAt(0, "").formErrorTask(tasks[i], e.getCode(), e.getMessage());
							if (tasks[i]->job() != GENERATE_ERROR_PAGE)
								continue ;
						}

						if (tasks[i]->job() == AUTOINDEX || tasks[i]->job() == GENERATE_ERROR_PAGE)
						{
							TCP::sendMessage(tasks[i]->getFD(), (std::string)tasks[i]->doJob());
							TCP::closeConnection(tasks[i]->getFD());
							Task* task = tasks[i];
							tasks.erase(tasks.begin() + i);
							--i;
							delete task;
						}
					}
					else
					{
						// Выполнить задачу
						HTTPResponse response = tasks[i]->doJob();

						std::string message = (std::string)response;
						size_t n = message.length() / MAX_HTTP;
						size_t reminded = message.length() % MAX_HTTP;
						size_t offset = 0;
						for (size_t j = 0; j < n; ++j)
						{
							TCP::sendMessage(tasks[i]->returnFD(), message.substr(offset, MAX_HTTP));
							offset += MAX_HTTP;
						}
						TCP::sendMessage(tasks[i]->returnFD(), message.substr(offset, reminded));

						TCP::closeConnection(tasks[i]->returnFD());
						Task* task = tasks[i];
						tasks.erase(tasks.begin() + i);
						--i;
						delete task;
					}
				}
			}
		}
	}
	catch(const std::runtime_error& e)
	{
		throw e;
	}
}
