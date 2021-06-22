/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPMessage.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 00:18:35 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/22 22:37:19 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_MESSAGE
#define HTTP_MESSAGE

#include <string>
#include <map>
#include "Utilities.hpp"

class HTTPMessage {
protected:
	std::map<std::string, std::string, cmpCaseInsensetive>	_header_fields;
	std::string												_body;
	size_t													_uri_max_length;

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
