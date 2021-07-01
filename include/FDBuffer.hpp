/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDBuffer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 05:49:47 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/29 06:01:53 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDBUFFER_H__
#define __FDBUFFER_H__

#include <cstdio>
#include <cstring>
#include <streambuf>
#include <unistd.h>

#define IN_BUFFER_SIZE 262144

class FDBuffer : public std::streambuf
{
protected:
	int		_fd;
	char	_buffer[IN_BUFFER_SIZE];

public:
	FDBuffer(int fd);
	~FDBuffer();

	int_type underflow();
};

#endif // __FDBUFFER_H__
