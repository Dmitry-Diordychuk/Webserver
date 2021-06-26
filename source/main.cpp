/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:55:24 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/25 15:19:03 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "Server.hpp"
#include "VirtualServer.hpp"
#include "ParseConfig.hpp"

int main()
{
	// ParseConfig start;
	// start.ParseConf();

	// Config conf;
	// for (size_t i = 0; i < start.getServInfo().size(); ++i)
	// {
	// 	ParseConfig* server_info = start.getServInfo()[i];
	// 	std::map<std::string, std::string> head_fields = server_info->getMapHeadFields();
	// 	VirtualServer server(head_fields["host"], "", atoi(head_fields["port"].c_str()));

	// 	server.setMaxBodySize(atoi(head_fields["max_body_size"].c_str()));

	// 	std::map<std::string, std::string> error_pages = server_info->getErrorPages();
	// 	std::map<std::string, std::string>::iterator error_it = error_pages.begin();
	// 	for (; error_it != error_pages.end(); ++error_it)
	// 		server.addErrorPage(atoi(error_it->first.c_str()), error_it->second);

	// 	size_t loc_size = server_info->getLocPath().size();
	// 	for (size_t j = 0; j < loc_size; ++j)
	// 	{
	// 		std::string location_path = server_info->getValueLocPath()[j];
	// 		Location location(location_path);

	// 		location.setRoot( server_info->getMapLoc()[location_path]["root"] );
	// 		location.setIndex( server_info->getMapLoc()[location_path]["index"] );

	// 		std::vector<Method> methods;
	// 		for (
	// 			size_t k = 0; server_info->getMethods()[loc_size].find(k) !=
	// 						  server_info->getMethods()[loc_size].end(); ++k
	// 		) {
	// 			methods.push_back(strToMethod(server_info->getMethods()[loc_size][k]));
	// 		}
	// 		location.setAllowedMethods(methods);

	// 		location.setCgi( server_info->getMapLoc()[location_path]["cgi_extension"] );
	// 		if (server_info->getMapLoc()[location_path]["autoindex"] == "on")
	// 			location.setAutoindex(true);
	// 		else
	// 			location.setAutoindex(false);

	// 		server.addLocation(location);
	// 	}
	// 	conf.addVirtualServer(server);
	// }
	// conf.setMaxSockets(1000000);
	// conf.socketTimeout(1);

	VirtualServer virtserver_localhost("localhost", "", 8080);
	virtserver_localhost.addErrorPage(404, "./../test/www/error404.html");

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

	Location location5("/post");
	location5.setAllowedMethods(methods_default);
	location5.setRoot("./../test/www/");
	location5.setMaxBodySize(1000);
	location5.setAutoindex(true);
	location5.setUploadDirectory("/tmp/");

	Location location6("/index/");
	location6.setAllowedMethods(methods_default);
	location6.setRoot("./../test/www/");
	location6.setAutoindex(true);

	virtserver_localhost.addLocation(location1);
	virtserver_localhost.addLocation(location2);
	virtserver_localhost.addLocation(location3);
	virtserver_localhost.addLocation(location5);
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

	Location location3_2("/auto/");
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
