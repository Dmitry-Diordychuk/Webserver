/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 01:54:27 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/29 23:53:30 by kdustin          ###   ########.fr       */
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

void HTTPMessage::deleteField(std::string name)
{
	_header_fields.erase(name);
}

void HTTPMessage::setUriMaxLength(size_t len)
{
	_uri_max_length = len;
}

std::string HTTPMessage::getHeaderFields()
{
	std::string str;
	std::map<std::string, std::string>::reverse_iterator it = _header_fields.rbegin();
	for (; it != _header_fields.rend(); ++it)
		str += (*it).first + ':' + (*it).second + "\r\n";
	str += "\r\n";
	return (str);
}

size_t HTTPMessage::bodyLength()
{
	return (_body.length());
}

HTTPMessage::operator std::string() {
	std::string str;
	std::map<std::string, std::string>::reverse_iterator it = _header_fields.rbegin();
	for (; it != _header_fields.rend(); ++it)
		str += (*it).first + ':' + (*it).second + "\r\n";
	str += "\r\n" + _body;
	return (str);
}

void HTTPMessage::setBody(std::string body)
{
	_body = body;
}
