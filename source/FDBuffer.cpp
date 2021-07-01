/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDBuffer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 05:50:49 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/29 05:51:03 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FDBuffer.hpp"

FDBuffer::FDBuffer(int fd)
{
	_fd = fd;
	setg(_buffer, _buffer, _buffer);
}

FDBuffer::~FDBuffer()
{
}

FDBuffer::int_type FDBuffer::underflow() {
	if (_fd < 0)
		return (EOF);

	if (gptr() < egptr())
		return traits_type::to_int_type(*gptr());

	int num;
	num = read(_fd, _buffer, IN_BUFFER_SIZE);
	if (num <= 0)
		return (EOF);

	setg(_buffer, _buffer, _buffer + num);
	return traits_type::to_int_type(*gptr());
}
