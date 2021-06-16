/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:52:15 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 17:33:46 by kdustin          ###   ########.fr       */
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
		Desc descs;
		// Инициализация сокетов
		for (size_t i = 0; i < _config.size(); ++i)
		{
			int server_sd = TCP::createConnectionSocket();
			TCP::bindConnectionSocket(server_sd, _config.getIpAt(i), _config.getPortAt(i));
			TCP::startListen(server_sd, _config.getMaxSockets());

			descs.addDesc(server_sd, LISTEN);
		}

		// Основной цикл
		while (1)
		{
			// Для каждого набора серверных сокетов.
			for (size_t i = 0; i < descs.size(); ++i)
			{
				if (poll(descs.getPollfdSet(), descs.size(), _config.getSocketTimeout()) < 0)
					throw std::runtime_error(std::string(strerror(errno)));

				if (descs.readyToRead(i))
				{
					if (descs.getType(i) == LISTEN)
					{
						// Устанавливает TCP соединение.
						int new_socket = TCP::acceptConnection(descs.getFD(i));
						descs.addDesc(new_socket, REQUEST);
					}
					else if (descs.getType(i) == REQUEST)
					{
						// Принимает запрос
						std::stringstream message;
						message << TCP::reciveMessage(descs.getFD(i));

						// Парсинг запроса
						HTTPRequest request(8000);
						try
						{
							request.parseRequest(message);
						}
						catch(const std::exception& e)
						{
							std::cerr << e.what() << '\n'; // Header error return
							TCP::closeConnection(descs.getFD(i));
							descs.delDesc(i);
							continue ;
						}

						// Обработать запрос и сформировать задачу
						Task task;
						task = _config.getVirtualServerAt(i, request.getHostField()).processRequest(request);
						descs.addDesc(task);
					}
					else if (descs.getType(i) == TASK)
					{
						// Выполнить задачу
						Task task = descs.getTask(i);
						HTTPResponse response = task.doJob();

						// Отправить ответ
						TCP::sendMessage(descs.getFD(i), response.toStr());
						TCP::closeConnection(descs.getFD(i));
						descs.delDesc(i);
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
