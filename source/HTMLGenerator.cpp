/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTMLGenerator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:28:47 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/17 11:52:01 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTMLGenerator.hpp"

std::string HTMLGenerator::Autoindex(Directory *dir)
{
	std::string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body +=		"<h1>Index of " + dir->getPath() + "</h1>";
	body +=		"<pre><hr>";

	std::string name;
	while ((name = dir->getNextName()) != "")
	{
		body += "<a href=\"" + dir->getPath() + "/" + name + "\">";
		if (dir->isDir())
		{
			body += name;
			body += '/';
		}
		else
			body += name;
		body += "</a>\n";
	}

	body +=		"</pre><hr>";
	body +=	"</html>";
	return (body);
}
