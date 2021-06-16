/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPMessage.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 00:18:35 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/13 04:47:46 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_MESSAGE
#define HTTP_MESSAGE

#include <string>
#include <map>

class HTTPMessage {
protected:
	std::map<std::string, std::string>	_header_fields;
	std::string							_body;
	size_t								_uri_max_length;

public:
	HTTPMessage();
	HTTPMessage(const HTTPMessage& other);
	HTTPMessage& operator=(const HTTPMessage& rhs);
	~HTTPMessage();

	void addField(std::string name, std::string value);
	void setBody(std::string body);
	void setUriMaxLength(size_t len);

	size_t bodyLength();

	std::string toStr();
};

#endif // HTTPMessage
