/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 01:25:05 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/26 22:26:17 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(size_t uri_max_length){
	_uri_max_length = uri_max_length;
}
HTTPRequest::~HTTPRequest() {}

bool ischar(unsigned char c)
{
	return (c >= 0 && c <= 127);
}

bool isctl(unsigned char c)
{
	return ((c >= 0 && c <= 31) || c == 127);
}

bool isseparator(unsigned char c)
{
	return (c == '(' || c == ')' || c == '<' || c == '>' || c == '@' || c == ','
	|| c == ';' || c == ':' || c == '\\' || c == '\"' || c == '/' || c == '[' ||
	c == ']' || c == '?' || c == '?' || c == '=' || c == '{' || c == '}' ||
	c == ' ' || c == 9);
}

bool ishex(unsigned char c)
{
	return (isdigit(c) || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F');
}

bool isunreserved(unsigned char c)
{
	return (isalnum(c) || c == '-' || c == '.' || c == '_' || c == '~');
}

bool ispct_encoded(std::stringstream &stream)
{
	bool result = false;
	char pct;
	char n1;
	char n2;

	stream.get(pct);
	if (pct == '%')
	{
		stream.get(n1);
		if (isdigit(n1))
		{
			stream.get(n2);
			if (isdigit(n2))
				result = true;
			stream.putback(n2);
		}
		stream.putback(n1);
	}
	stream.putback(pct);
	return (result);
}

bool issub_delim(unsigned char c)
{
	return (c == '!' || c == '$' || c == '&' || c == 96 || c == '(' || c == ')'
			||c == '*' || c == '+' || c == ',' || c == ';' || c == '=');
}

bool ispchar(std::stringstream &stream)
{
	char c = stream.peek();
	return (isunreserved(c) || ispct_encoded(stream) || issub_delim(c) ||
	c == ':' || c == '@');
}

bool isfield_vchar(unsigned char c)
{
	return (isprint(c) || c > 127);
}

std::string tryParseToken(std::stringstream &stream)
{
	bool one = false;
	char c;
	std::list<unsigned char> buffer;
	std::string token;

	while ((c = stream.peek()))
	{
		if (ischar(c) && !isctl(c) && !isseparator(c))
			buffer.push_back(stream.get());
		else
			break ;
		one = true;
	}
	if (one == false)
	{
		while (!buffer.empty())
		{
			stream.putback(buffer.back());
			buffer.pop_back();
		}
	}
	while (!buffer.empty())
	{
		token += buffer.front();
		buffer.pop_front();
	}
	return (token);
}

std::string tryParseSegment(std::stringstream &stream)
{
	char c;
	std::string segment;

	stream.get();
	while ((c = stream.peek()))
	{
		if (ispchar(stream))
			segment += stream.get();
		else
			break ;
	}
	return (segment);
}

std::string tryParseSegmentNz(std::stringstream &stream)
{
	bool one = false;
	char c;
	std::list<unsigned char> buffer;
	std::string segment;

	while ((c = stream.peek()))
	{
		if (ispchar(stream))
			buffer.push_back(stream.get());
		else
			break ;
		one = true;
	}
	if (one == false)
	{
		while (!buffer.empty())
		{
			stream.putback(buffer.back());
			buffer.pop_back();
		}
	}
	while (!buffer.empty())
	{
		segment += buffer.front();
		buffer.pop_front();
	}
	return (segment);
}

Path parsePathAbsolute(std::stringstream &stream)
{
	Path	path;

	char c;
	stream.get(c);
	if (c != '/')
		throw HTTPException(BAD_REQUEST_ERROR);
	path.setIsEmpty(false);
	std::string segment_nz = tryParseSegmentNz(stream);
	if (segment_nz.empty())
	{
		path.setIsDirectory(true);
		return (path);
	}
	path.addSegment(segment_nz);
	while (stream.peek() == '/')
	{
		std::string segment = tryParseSegment(stream);
		if (!segment.empty())
			path.addSegment(segment);
		else
			path.setIsDirectory(true);
	}
	return (path);
}

std::string tryParseQuery(std::stringstream &stream)
{
	char c;
	std::string query;

	while ((c = stream.peek()))
	{
		if (ispchar(stream) || c == '/' || c == '?')
		{
			query += stream.get();
		}
		else
			break ;
	}
	return (query);
}

HTTP_request_line	HTTPRequest::getStartLine(){
	return (_request_line);
}

void HTTPRequest::checkSP(std::stringstream &stream)
{
	if (stream.get() != ' ')
		throw HTTPException(BAD_REQUEST_ERROR);
}

void HTTPRequest::checkCRLF(std::stringstream &stream)
{
	char c;
	stream.get(c);
	if (c != '\r')
		throw HTTPException(BAD_REQUEST_ERROR);
	stream.get(c);
	if (c != '\n')
		throw HTTPException(BAD_REQUEST_ERROR);
}

void HTTPRequest::parseMethod(std::stringstream &stream)
{
	std::string token;
	token = tryParseToken(stream);
	if (token.empty())
		throw HTTPException(NOT_IMPLEMENTED_ERROR);
	if (token != "GET" &&
		token != "HEAD" &&
		token != "POST" &&
		token != "DELETE")
		throw HTTPException(NOT_IMPLEMENTED_ERROR);
	_request_line.method = strToMethod(token);
}

void HTTPRequest::parseRequestTarget(std::stringstream &stream)
{
	char c;

	_request_line.uri.setPath(parsePathAbsolute(stream));
	while ((c = stream.peek()) == '?')
		_request_line.uri.setQuery(tryParseQuery(stream));

	if (_request_line.uri.length() > _uri_max_length)
		throw HTTPException(URI_TOO_LONG_ERROR);
}

void HTTPRequest::parseHTTPVersion(std::stringstream &stream)
{
	char c;
	stream.get(c);
	if (c != 'H')
		throw HTTPException(BAD_REQUEST_ERROR);
	_request_line.version += c;
	for (size_t i = 0; i < 2; ++i)
	{
		stream.get(c);
		if (c != 'T')
			throw HTTPException(BAD_REQUEST_ERROR);
		_request_line.version += c;
	}
	stream.get(c);
	if (c != 'P')
		throw HTTPException(BAD_REQUEST_ERROR);
	_request_line.version += c;
	stream.get(c);
	if (c != '/')
		throw HTTPException(BAD_REQUEST_ERROR);
	_request_line.version += c;
	stream.get(c);
	if (c != '1')
		throw HTTPException(VERSION_NOT_SUPPORTED);
	if (!isdigit(c))
		throw HTTPException(BAD_REQUEST_ERROR);
	_request_line.version += c;
	stream.get(c);
	if (c != '.')
		throw HTTPException(BAD_REQUEST_ERROR);
	_request_line.version += c;
	stream.get(c);
	if (c != '1')
		throw HTTPException(VERSION_NOT_SUPPORTED);
	if (!isdigit(c))
		throw HTTPException(BAD_REQUEST_ERROR);
	_request_line.version += c;
}

bool trySkipObsFold(std::stringstream &stream)
{
	char c = stream.peek();
	if (c == '\r')
	{
		stream.get();
		c = stream.peek();
		if (c == '\n')
		{
			stream.get();
			c = stream.peek();
			if (c != ' ' && c != 9)
			{
				stream.putback('\n');
				stream.putback('\r');
				return (false);
			}
			stream.get();
			while ((c = stream.peek()) == ' ' || c == 9)
				;
			return (true);
		}
		else
			throw HTTPException(BAD_REQUEST_ERROR);
	}
	return (false);
}

std::string tryParseFieldContent(std::stringstream &stream)
{
	std::string					field_content;
	std::list<unsigned char>	buffer;
	char c = stream.peek();

	bool last_vchar = false;
	if (!isfield_vchar(c))
		return (field_content);
	else
		last_vchar = true;
	buffer.push_back(stream.get());

	while ((c = stream.peek()))
	{
		if (c == ' ' || c == 9)
		{
			buffer.push_back(stream.get());
			last_vchar = false;
		}
		else if (isfield_vchar(c))
		{
			buffer.push_back(stream.get());
			last_vchar = true;
		}
		else
			break ;
	}
	if (last_vchar == false)
		throw HTTPException(BAD_REQUEST_ERROR);

	while (!buffer.empty())
	{
		field_content += buffer.front();
		buffer.pop_front();
	}
	return (field_content);
}

std::string tryParseFieldValue(std::stringstream &stream)
{
	std::string field_value;
	std::string content;
	bool skip = true;
	while (skip || !content.empty())
	{
		content.clear();
		skip = trySkipObsFold(stream);
		content += tryParseFieldContent(stream);
		field_value += content;
	}
	return (field_value);
}

bool checkContentLength(std::string value)
{
	std::string::iterator it = value.begin();
	for (; it != value.end(); ++it)
	{
		if (!isdigit(*it))
			return (false);
	}
	int val = atoi(value.c_str());
	if (val < 0)
		return (false);
	return (true);
}

bool cmpCaseInsensetive(const std::string& a, const std::string& b)
{
	std::string::const_iterator ita = a.begin();
	std::string::const_iterator itb = b.begin();
	for (; ita != a.end() && itb != b.end(); ++ita, ++itb)
	{
		if (std::tolower(*ita) != std::tolower(*itb))
			return (false);
	}
	if (ita != a.end() || itb != b.end())
		return (false);
	return (true);
}

void HTTPRequest::parseHeaderFields(std::stringstream &stream)
{
	char		c;
	std::string	field_name;
	std::string	field_value;
	int host_counter = 0;
	int length_counter = 0;

	while (!(field_name = tryParseToken(stream)).empty())
	{
		if (cmpCaseInsensetive(field_name, "host"))
		{
			++host_counter;
			if (host_counter > 1)
				throw HTTPException(BAD_REQUEST_ERROR);
		}
		if ((c = stream.peek()) == ':')
		{
			stream.get();
			if (stream.peek() == ' ')
				stream.get();
			field_value = tryParseFieldValue(stream);
			if (stream.peek() == ' ')
				stream.get();
		}
		else
			throw HTTPException(BAD_REQUEST_ERROR);
		if (cmpCaseInsensetive(field_name, "Content-Length"))
		{
			if (!checkContentLength(field_value))
				throw HTTPException(BAD_REQUEST_ERROR);
			++length_counter;
			if (length_counter > 1)
				throw HTTPException(BAD_REQUEST_ERROR);
		}
		_header_fields[field_name] = field_value;
		stream.get(c);
		if (c != '\r')
			throw HTTPException(BAD_REQUEST_ERROR);
		stream.get(c);
		if (c != '\n')
			throw HTTPException(BAD_REQUEST_ERROR);
		field_name.clear();
	}
}

void HTTPRequest::parseRequest(std::stringstream &stream)
{
	// Parse start line
	try
	{
		parseMethod(stream);
		checkSP(stream);
		parseRequestTarget(stream);
		checkSP(stream);
		parseHTTPVersion(stream);
		checkCRLF(stream);
		parseHeaderFields(stream);
		checkCRLF(stream);
	}
	catch(const HTTPException& e)
	{
		throw e;
	}
	char c;
	while (stream.get(c))
		_body += c;
}

Path HTTPRequest::getPath()
{
	return (_request_line.uri.getPath());
}

Method HTTPRequest::getMethod()
{
	return (_request_line.method);
}

std::string HTTPRequest::getHostField()
{
	std::map<std::string, std::string, mapCmpCaseInsensetive>::iterator it = _header_fields.find("Host");
	if (it == _header_fields.end())
		throw HTTPException(BAD_REQUEST_ERROR);
	std::string host = it->second;
	size_t i = host.find_first_of(":");
	if (i != host.npos)
		return (host.substr(0, i));
	return (host);
}

bool HTTPRequest::isChunked()
{
	std::map<std::string, std::string, mapCmpCaseInsensetive>::iterator it = _header_fields.find("Transfer-Encoding");
	if (it == _header_fields.end())
		return (false);
	if (it->second == "chunked")
		return (true);
	return (false);
}

void HTTPRequest::changeChunkedToLength()
{
	_header_fields["Transfer-Encoding"] = "";
	_header_fields["Content-Length"] = intToStr(_body.length());
}

std::string HTTPRequest::getBody()
{
	return (_body);
}
