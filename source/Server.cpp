/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:52:15 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/26 22:24:34 by kdustin          ###   ########.fr       */
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
			fcntl(server_sd, F_SETFL, O_NONBLOCK);
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
							TCP::sendMessage(tasks[i]->getFD(), tasks[i]->doJob().toStr());
							TCP::closeConnection(tasks[i]->getFD());
							tasks.erase(tasks.begin() + i);
							--i;
						}
					}
					else
					{
						// Выполнить задачу
						HTTPResponse response = tasks[i]->doJob();

						// Отправить ответ
						TCP::sendMessage(tasks[i]->returnFD(), response.toStr());
						TCP::closeConnection(tasks[i]->returnFD());
						tasks.erase(tasks.begin() + i);
						--i;
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
