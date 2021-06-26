/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkedBody.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:12:32 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/26 06:08:28 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CHUNKEDBODY_H__
#define __CHUNKEDBODY_H__

#include <string>
#include <sstream>
#include <limits>
#include <algorithm>

enum State {
	Complete,
	DecodeSize,
	ReadChunkBody,
	DecodeTrailer,
	Error
};

class ChunkedBody
{
public:
	ChunkedBody();
	ChunkedBody(ChunkedBody&);
	ChunkedBody& operator=(ChunkedBody&);
	~ChunkedBody();

	void decode(std::string input);

	State getState();

	operator std::string();

	struct Impl {
		State state;
		std::stringstream decoded_body;
		size_t current_chunk_size;
		size_t current_body_position;
		std::stringstream input_buffer;
	};
private:
	Impl *_impl;
	bool checkCRLF();
};

#endif // __CHUNKEDBODY_H__
