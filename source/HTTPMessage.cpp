/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 01:54:27 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/13 18:51:31 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPMessage.hpp"

HTTPMessage::HTTPMessage() {}

HTTPMessage::~HTTPMessage() {}

HTTPMessage::HTTPMessage(const HTTPMessage& other)
{
	_body = other._body;
	_header_fields = other._header_fields;
	_uri_max_length = other._uri_max_length;
}

HTTPMessage& HTTPMessage::operator=(const HTTPMessage& rhs)
{
	if (&rhs == this)
		return (*this);
	_body = rhs._body;
	_header_fields = rhs._header_fields;
	_uri_max_length = rhs._uri_max_length;
	return (*this);
}

void HTTPMessage::addField(std::string name, std::string value)
{
	_header_fields[name] = value;
}

void HTTPMessage::setUriMaxLength(size_t len)
{
	_uri_max_length = len;
}

size_t HTTPMessage::bodyLength()
{
	size_t len = _body.length();
	if (len > 0)
		return (len - 1);
	return (0);
}

std::string HTTPMessage::toStr()
{
	std::string str;
	std::map<std::string, std::string>::iterator it = _header_fields.begin();
	for (; it != _header_fields.end(); ++it)
		str += (*it).first + ':' + (*it).second + "\r\n";
	str += "\r\n" + _body;
	return (str);
}

void HTTPMessage::setBody(std::string body)
{
	_body = body;
}
