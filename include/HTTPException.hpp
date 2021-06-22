/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 00:38:04 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/22 19:47:32 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_EXCEPTION
#define HTTP_EXCEPTION

#include <string>

class HTTPException : public std::exception
{
private:
	size_t		_code;
	std::string	_message;

public:
	HTTPException(size_t code, std::string message) throw();
	virtual ~HTTPException() throw();
	HTTPException& operator=( const HTTPException& other ) throw();

	size_t		getCode() const;
	std::string	getMessage() const;
	const char* what() const throw();
};

// Client Errors
#define BAD_REQUEST_ERROR		400, "Bad Request"
#define NOT_ALLOWED_ERROR		405, "Method Not Allowed"
#define URI_TOO_LONG_ERROR		414, "URI Too Long"

// Server Errors
#define INTERNAL_SERVER_ERROR	500, "Internal Server Error"
#define NOT_IMPLEMENTED_ERROR	501, "Not Implemented"
#define VERSION_NOT_SUPPORTED	505, "HTTP Version Not Supported"

#endif // HTTP_EXCEPTION
