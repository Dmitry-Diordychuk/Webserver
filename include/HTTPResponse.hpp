/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 01:22:09 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/23 01:35:42 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

class HTTPResponse;

#include "HTTPRequest.hpp"

#include <sstream>

#ifdef DEBUG
#include <iostream>
#endif

struct HTTP_status_line
{
	std::string	http_version;
	size_t		status_code;
	std::string	reason_phrase;
};

class HTTPResponse : public HTTPMessage
{
private:
	HTTP_status_line	_status_line;

public:
	HTTPResponse();
	HTTPResponse(size_t code, std::string reason);
	~HTTPResponse();

	void setStatusLine(std::string ver, size_t code, std::string phrase);
	void setBody(std::string body);
	std::string toStr();

	size_t getCode();
	std::string getReason();
};

#endif // HTTP_RESPONSE_HPP
