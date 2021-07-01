/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTMLGenerator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:28:47 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/27 18:09:29 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTMLGenerator.hpp"

std::string HTMLGenerator::Autoindex(Directory *dir, std::string uri)
{
	std::string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body +=		"<h1>Index of " + uri + "</h1>";
	body +=		"<pre><hr>";

	std::string name;
	while ((name = dir->getNextName()) != "")
	{
		std::string::reverse_iterator rit = uri.rbegin();
		if (*rit == '/')
			body += "<a href=\"" + uri + name + "\">";
		else
			body += "<a href=\"" + uri + "/" + name + "\">";
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
