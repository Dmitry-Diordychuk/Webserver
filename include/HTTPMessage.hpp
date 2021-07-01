/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPMessage.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 00:18:35 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/29 23:52:51 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_MESSAGE
#define HTTP_MESSAGE

#include <string>
#include <map>
#include "Utilities.hpp"

class HTTPMessage {
protected:
	std::map<std::string, std::string, mapCmpCaseInsensetive>	_header_fields;
	std::string													_body;
	size_t														_uri_max_length;

public:
	HTTPMessage();
	HTTPMessage(const HTTPMessage& other);
	HTTPMessage& operator=(const HTTPMessage& rhs);
	~HTTPMessage();

	void addField(std::string name, std::string value);
	void deleteField(std::string name);
	void setBody(std::string body);
	void setUriMaxLength(size_t len);
	std::string getHeaderFields();

	size_t bodyLength();

	operator std::string();
};

#endif // HTTPMessage
