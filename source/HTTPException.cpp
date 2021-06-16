/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPException.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 00:41:06 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/10 01:30:54 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPException.hpp"

HTTPException::HTTPException(size_t code, std::string message) throw()
	: _code(code), _message(message) {}

HTTPException::~HTTPException() throw() {}

HTTPException& HTTPException::operator=( const HTTPException& other ) throw()
{
	_code = other._code;
	_message = other._message;
	return (*this);
}

size_t HTTPException::getCode(){
	return (_code);
}

std::string HTTPException::getMessage() {
	return (_message);
}

const char* HTTPException::what() const throw() {
	return ("HTTP exception!");
}
