/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 01:23:50 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/26 22:22:02 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

class HTTPRequest;

#include "Utilities.hpp"
#include "HTTPMessage.hpp"
#include "HTTPException.hpp"
#include "URI.hpp"
#include "Method.hpp"

#include <list>

struct HTTP_request_line
{
	Method		method;
	URI			uri;
	std::string	version;
};

class HTTPRequest : public HTTPMessage
{
private:
	HTTP_request_line	_request_line;

	HTTPRequest();

	void checkSP(std::stringstream &stream);
	void checkCRLF(std::stringstream &stream);
	void parseMethod(std::stringstream &stream);
	void parseRequestTarget(std::stringstream &stream);
	void parseHTTPVersion(std::stringstream &stream);
	void parseHeaderFields(std::stringstream &stream);

public:
	HTTP_request_line	getStartLine();
	HTTPRequest(size_t uri_max_length);
	virtual ~HTTPRequest();

	void parseRequest(std::stringstream &stream);
	Path getPath();
	Method getMethod();
	std::string getHostField();
	std::string getBody();
	bool isChunked();
	void changeChunkedToLength();
};



#endif // HTTP_REQUEST_HPP
