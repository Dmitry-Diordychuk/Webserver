/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTMLGenerator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:28:47 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 17:35:56 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTMLGenerator.hpp"

std::string HTMLGenerator::Autoindex(Directory dir)
{
	std::string body;
	body += dir.getNextName();
	// body += "<!DOCTYPE html>";
	// body += "<html>";
	// body +=		"<h1>Index of " + path.toStr() + "</h1>";
	// body +=		"<pre><hr>";

	// DIR *dir;
	// std::string name;
	// while ((name = dir.getNextName()) != "")
	// {
	// 	body += "<a href=\"" + path.toStr() + "/" + ent->d_name + "\">";
	// 	if (ent->d_type == DT_DIR)
	// 	{
	// 		body += ent->d_name;
	// 		body += '/';
	// 	}
	// 	else if (ent->d_type == DT_REG)
	// 		body += ent->d_name;
	// 	body += "</a>";
	// }
	// if ((dir = opendir((path.toStr()).c_str())) != NULL)
	// {
	// 	while ((ent = readdir(dir)) != NULL)
	// 	{
	// 		body += "<a href=\"" + path.toStr() + "/" + ent->d_name + "\">";
	// 		if (ent->d_type == DT_DIR)
	// 		{
	// 			body += ent->d_name;
	// 			body += '/';
	// 		}
	// 		else if (ent->d_type == DT_REG)
	// 			body += ent->d_name;
	// 		body += "</a>";
	// 	}
	// 	closedir(dir);
	// }
	// else
	// 	throw std::runtime_error(strerror(errno));
	// body +=		"</pre><hr>";
	// body +=	"</html>";
	return (body);
}
