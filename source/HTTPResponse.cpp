/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 01:23:05 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/17 18:58:15 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPResponse.hpp"

HTTPResponse::HTTPResponse() {}
HTTPResponse::~HTTPResponse() {}

void HTTPResponse::setStatusLine(std::string ver, size_t code, std::string phrase)
{
	_status_line.http_version = ver;
	_status_line.status_code = code;
	_status_line.reason_phrase = phrase;
}

void HTTPResponse::setBody(std::string body)
{
	_body = body;
	addField("Content-Length", intToStr(body.length()));
}

HTTPResponse::HTTPResponse(size_t code, std::string reason)
{
	_status_line.http_version = "HTTP/1.1";
	_status_line.status_code = code;
	_status_line.reason_phrase = reason;
}

std::string HTTPResponse::toStr()
{
	std::string message;
	message += _status_line.http_version + ' ';
	message += intToStr(_status_line.status_code) + ' ';
	message += _status_line.reason_phrase + "\r\n";
	message += HTTPMessage::toStr();
	return (message);
}
