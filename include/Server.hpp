/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:34:22 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 16:56:42 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>

#include "Config.hpp"
#include "TCP.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "Desc.hpp"
#include "HTMLGenerator.hpp"
#include <poll.h>

class Server
{
private:
	Config	_config;

public:
	Server();
	Server(Config conf);
	~Server();

	void start();
};

#endif // SERVER_HPP