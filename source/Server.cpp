/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:52:15 by kdustin           #+#    #+#             */
/*   Updated: 2021/07/03 02:04:36 by kdustin          ###   ########.fr       */
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
		//std::vector<Task*> tasks;
		Descriptors descriptors;
		std::vector<ConnectionSocket*> servers;
		// Инициализация сокетов
		for (size_t i = 0; i < _config.size(); ++i)
		{
			ConnectionSocket *connection_socket = new ConnectionSocket();
			connection_socket->listen(_config.getIpAt(i), _config.getPortAt(i));
			descriptors.add(connection_socket);
			servers.push_back(connection_socket);
		}

		std::vector<Task*> tasks;
		// Основной цикл
		while (1)
		{
			descriptors.poll();

			// Установить новые TCP соединения
			ClientSocket *client_socket;
			for (size_t i = 0; i < servers.size(); ++i)
			{
				if ((client_socket = servers[i]->accept()))
				{
					descriptors.add(client_socket);
					tasks.push_back(new Task(SocketRead, HTTPResponse(), NULL, "", client_socket));
				}
			}


			for (size_t i = 0; i < tasks.size(); ++i)
			{
				// Принять запросы
				if (tasks[i]->job() == SocketRead)
				{
					ClientSocket *socket = tasks[i]->getSocket();
					if (socket->readReady())
					{
						if (socket->read(tasks[i]->getStorage()))
						{
							// Чтение законченно
							std::string message = tasks[i]->getStorage();
							tasks[i]->changeJob(ProcessRequest, HTTPResponse(), NULL, message);
						}
					}
				}
				else if (tasks[i]->job() == ProcessRequest)
				{
					HTTPRequest request(8000);
					try
					{
						std::stringstream message(tasks[i]->getStorage());
						// Парсинг запроса
						request.parseRequest(message);

						if (request.isChunked())
						{
							ChunkedBody chunked_body;
							chunked_body.decode(request.getBody());
							if (chunked_body.getState() == Complete)
							{
								request.setBody((std::string)chunked_body);
								request.changeChunkedToLength();
							}
							else
								throw HTTPException(BAD_REQUEST_ERROR);
						}

						// Обработать запрос и сформировать задачу
						ClientSocket *socket = tasks[i]->getSocket();
						VirtualServer *virt_server = _config.getVirtualServer(socket, request.getHostField());
						if (virt_server) {
							virt_server->processRequest(request, tasks[i]);
							descriptors.add(tasks[i]);
						} else {
							throw HTTPException(INTERNAL_SERVER_ERROR);
						}
					}
					catch(const HTTPException& e)
					{
						ClientSocket *socket = tasks[i]->getSocket();
						VirtualServer *virt_server = _config.getVirtualServer(socket, "");
						if (virt_server) {
							virt_server->formErrorTask(e.getCode(), e.getMessage(), tasks[i]);
							descriptors.add(tasks[i]);
						} else {
							throw std::runtime_error("HTTP Exception Error: can't find proper virtual server!");
						}
						continue ;
					}
				}
				else if (tasks[i]->job() == SocketWrite)
				{
					// Вывод ответа и завершение задачи
					ClientSocket *socket = tasks[i]->getSocket();
					if (socket->writeReady())
					{
						if (socket->write(tasks[i]->getStorage()))
						{
							Task *task = tasks[i];
							tasks.erase(tasks.begin() + i);
							--i;
							delete task;
						}
					}
				}
				else
				{
					// Подготовка ответа
					HTTPResponse response = tasks[i]->doJob();
					tasks[i]->changeJob(SocketWrite, HTTPResponse(), NULL, (std::string)response);
				}
			}
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		throw std::runtime_error("FATAL ERROR!");
	}
}
