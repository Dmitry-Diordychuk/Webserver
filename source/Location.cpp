/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 15:47:30 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/15 01:16:51 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location(std::string prefix)
	: _autoindex(false)
{
	_prefix = Path(prefix);
}

Location::~Location(){}

void Location::setRoot(std::string root)
{
	_root = Path(root);
}

void Location::setIndex(std::string index)
{
	_index = index;
}

void Location::setAllowedMethods(std::vector<Method> methods)
{
	_allowed_methods = methods;
}

void Location::setAutoindex(bool b)
{
	_autoindex = b;
}

void Location::setCgi(std::string cgi_path)
{
	_cgi = cgi_path;
}

void Location::setServerName(std::string server_name)
{
	_server_name = server_name;
}

std::string Location::getIndex()
{
	return (_index);
}

std::string Location::getPrefix()
{
	return (_prefix.toStr());
}

bool Location::getAutoindex()
{
	return (_autoindex);
}

bool Location::checkAllowedMethods(Method method)
{
	std::vector<Method>::iterator it = _allowed_methods.begin();
	for (; it != _allowed_methods.end(); ++it)
	{
		if (method == (*it))
			return (true);
	}
	return (false);
}

Path Location::checkLocation(Path path)
{
	Path result;
	Path::iterator fit;
	if (path.findSegment(_prefix, fit))
	{
		result = _root;
		for (; fit != path.end(); ++fit)
			result.addSegment(*fit);
	}
	return (result);
}
