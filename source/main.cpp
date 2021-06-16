/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:55:24 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/15 19:57:58 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "Server.hpp"
#include "VirtualServer.hpp"

int main()
{

	VirtualServer virtserver_localhost("localhost", "", 8080);
	virtserver_localhost.setErrorPage("./../test/www/error404.html");

	std::vector<Method> methods_default;
	methods_default.push_back(GET);
	methods_default.push_back(HEAD);
	methods_default.push_back(POST);
	methods_default.push_back(DELETE);

	std::vector<Method> methods1;
	methods1.push_back(GET);
	methods1.push_back(HEAD);

	Location location1("/");
	location1.setAllowedMethods(methods1);
	location1.setRoot("./../test/www/"); // Нужен ли слеш?
	location1.setIndex("index.html");
	location1.setAutoindex(false);

	Location location2("/2/");
	location2.setAllowedMethods(methods_default);
	location2.setRoot("./../test/www/");
	location2.setIndex("second.html");

	Location location3("/virtual/");
	location3.setAllowedMethods(methods_default);
	location3.setRoot("./../test/www/");

	//Location location4("/protected");

	//Location location5("/post");

	Location location6("/index/");
	location6.setAllowedMethods(methods_default);
	location6.setRoot("./../test/www/");
	location6.setAutoindex(true);

	virtserver_localhost.addLocation(location1);
	virtserver_localhost.addLocation(location2);
	virtserver_localhost.addLocation(location3);
	virtserver_localhost.addLocation(location6);


	VirtualServer virtserver_8081("localhost", "", 8081);

	Location location2_1("/");
	location2_1.setAllowedMethods(methods_default);
	location2_1.setRoot("./../test/www/");
	location2_1.setIndex("second.html");

	virtserver_8081.addLocation(location2_1);



	VirtualServer virtserver_google("google.com", "", 8080);

	Location location3_1("/");
	location3_1.setAllowedMethods(methods_default);
	location3_1.setRoot("./../test/www/");
	location3_1.setIndex("google.html");

	Location location3_2("/auto");
	location3_2.setAllowedMethods(methods_default);
	location3_2.setRoot("./../test/www/auto");
	location3_2.setAutoindex(true);

	virtserver_google.addLocation(location3_1);
	virtserver_google.addLocation(location3_2);



	Config conf;
	conf.addVirtualServer(virtserver_localhost);
	conf.addVirtualServer(virtserver_8081);
	conf.addVirtualServer(virtserver_google);
	conf.setMaxSockets(1000000);
	conf.socketTimeout(1);

	Server server(conf);
	try
	{
		server.start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
