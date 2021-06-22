/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 15:47:30 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/22 18:37:42 by kdustin          ###   ########.fr       */
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

void Location::setUploadDirectory(std::string dir)
{
	_upload_directory = Path(dir);
}

void Location::setMaxBodySize(size_t size)
{
	_max_body_size = size;
}

std::string Location::getIndex()
{
	return (_index);
}

std::string Location::getPrefix()
{
	return (_prefix.toStr());
}

bool Location::autoindex()
{
	return (_autoindex);
}

std::string Location::getUploadPath(Path request_path)
{
	Path result;
	Path::iterator it_req = request_path.begin();
	Path::iterator it_prefix = _prefix.begin();
	for (;*it_req == *it_prefix && it_req != request_path.end() && it_prefix != _prefix.end(); ++it_req, ++it_prefix)
		result.addSegment(*it_req);
	Path::iterator it_upload = _upload_directory.begin();
	for (;it_upload != _upload_directory.end(); ++it_upload)
		result.addSegment(*it_upload);
	for (;it_req != request_path.end(); ++it_req)
		result.addSegment(*it_req);
	result.setIsDirectory(false);
	result.setIsEmpty(false);
	return (result.toStr());
}

size_t Location::getMaxBodySize()
{
	return (_max_body_size);
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
		Path::iterator upload_it = _upload_directory.begin();
		if (fit != path.end() && upload_it != _upload_directory.end() && *upload_it != *fit)
			for (; upload_it != _upload_directory.end(); ++upload_it)
				result.addSegment(*upload_it);
		for (; fit != path.end(); ++fit)
			result.addSegment(*fit);
		result.setIsDirectory(path.directory());
	}
	return (result);
}
