/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkedBody.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:14:52 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/29 22:18:16 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChunkedBody.hpp"

ChunkedBody::ChunkedBody() {
	_impl = new Impl();
	_impl->state = DecodeSize;
	_impl->decoded_body.str(std::string());
	_impl->input_buffer.str(std::string());
}

ChunkedBody::ChunkedBody(ChunkedBody&) {}
ChunkedBody& ChunkedBody::operator=(ChunkedBody&) {return(*this);}
ChunkedBody::~ChunkedBody() {
	delete _impl;
}

// bool ishex(unsigned char c)
// {
// 	return ();
// }

bool istchar(unsigned char c)
{
	return (isalnum(c) || (c == '!') || (c == '#') || (c == '$') || (c == '%') || (c == '&') || (c == '\'') ||
			(c == '*') || (c == '+') || (c == '-') || (c == '.') || (c == '^') || (c == '_') || (c == '`') ||
			(c == '|') || (c == '~'));
}

bool isqdtext(unsigned char c)
{
	return ((c == '\t') || (c == ' ') || (c == '!') || (c >= 0x23 && c <= 0x5B) ||
			(c >= 0x5D && c <= 0x7E) || (c >= 0x80 && c <= 0xFF));
}

bool isvchar(unsigned char c)
{
	return (isprint(c));
}

bool isqpair(unsigned char c)
{
	return ((c == '\t') || (c == ' ') || isvchar(c) || (c >= 0x80 && c <= 0xFF));
}

size_t DecodeChunkSize(std::stringstream& input_stream)
{
	int state = 1;
	size_t chunk_size = 0;
	char c;
	bool name_parsed = false;
	size_t counter = 0;
	size_t counter_size_t = 0;
	while (
		(c = input_stream.peek())
		&& input_stream.rdbuf()->in_avail()
	) {
		if (counter > 4096 || counter_size_t > 20)
			state = -1;			// Too many symbols
		switch (state)
		{
		case 0: {				// decode succesful
			if (c == '\r')
			{
				input_stream.get();
				c = input_stream.peek();
				if (c == '\n')
				{
					input_stream.get();
					return (chunk_size);
				}
			}
			return (-1);
		} break;

		case 1:	{				// if chunk-size exist?
			if (isdigit(c) || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F') {
				state = 2;
			} else {
				state = -1;
			}
		} break;

		case 2: {				// parse chunk-size
			size_t digit = 0;
			if (isdigit(c)) {
				digit = (size_t)(input_stream.get() - '0');
				chunk_size <<= 4;
				chunk_size += digit;
				++counter_size_t;
			} else if (c >= 'A' && c <= 'F') {
				digit = (size_t)(input_stream.get() - 'A') + 10;
				chunk_size <<= 4;
				chunk_size += digit;
				++counter_size_t;
			} else if (c >= 'a' && c <= 'f') {
				digit = (size_t)(input_stream.get() - 'a') + 10;
				chunk_size <<= 4;
				chunk_size += digit;
				++counter_size_t;
			} else {
				state = 3;
			}
		} break;

		case 3: {				// if chunk-ext separator exist?
			if (c == ';') {
				state = 4;
				input_stream.get();
			} else {
				state = 0;
			}
		} break;

		case 4: { // chunk-ext token first char
			if (istchar(c)) {
				state = 5;
			} else {
				state = -1;
			}
		} break;

		case 5: { // parse chunk-ext token next char
			if (istchar(c)) {
				input_stream.get();
			} else if (name_parsed) {	// parse value
				state = 3;
				name_parsed = false;
			} else {					// parse name
				name_parsed = true;
				state = 6;
			}
		} break;

		case 6: { // chunk-ext-val eq exist?
			if (c == '=') {
				state = 7;
				input_stream.get();
			} else {
				state = 0;
			}
		} break;

		case 7: { // chunk token or quout-string?
			if (istchar(c)) {
				state = 4;
			} else if (c == '"') {
				input_stream.get();
				state = 8;
			} else {
				state = -1;
			}
		} break;

		case 8: { // chunk quout-string
			if (isqdtext(c)) {
				input_stream.get();
			} else if (c == '\\') {
				input_stream.get();
				state = 9;
			} else if (c == '"') {
				input_stream.get();
				state = 3;
				name_parsed = false;
			} else {
				state = -1;
			}
		} break;

		case 9: { // quote pair
			if (isqpair(c)) {
				input_stream.get();
				state = 8;
			} else {
				state = -1;
			}
		} break;

		case -1: { // decode failed
			return (-1);
		} break;
		}
		++counter;
	}
	if (chunk_size == 0)
		return (0);
	return (-1);
}

bool ChunkedBody::checkCRLF()
{
	if (_impl->input_buffer.peek() == '\r')
	{
		char c = _impl->input_buffer.get();
		if (_impl->input_buffer.peek() == '\n')
		{
			_impl->input_buffer.get();
			return (true);
		}
		_impl->input_buffer.putback(c);
	}
	return (false);
}

void ChunkedBody::decode(std::string input) {
	if (_impl->state == Complete || _impl->state == Error) { // Reset
		_impl->state = DecodeSize;
		_impl->decoded_body.str(std::string());
		_impl->input_buffer.str(std::string());
	}
	_impl->input_buffer << input;
	_impl->input_buffer.peek();
	while (
			_impl->input_buffer.rdbuf()->in_avail()
			&& _impl->state != Complete
			&& _impl->state != Error
	) {
		if (_impl->state == DecodeSize) {
			size_t offset = _impl->input_buffer.tellg();
			std::string str = _impl->input_buffer.str().substr(offset);
			if (str.find("\r\n") == std::string::npos)
				break ;
			if ((_impl->current_chunk_size = DecodeChunkSize(_impl->input_buffer)) == (size_t)-1) {
				_impl->state = Error;
				continue ;
			}
			_impl->state = ReadChunkBody;
			_impl->current_body_position = 0;
		}
		if (_impl->state == ReadChunkBody)
		{
			if (_impl->current_chunk_size == 0) {
				if (!_impl->input_buffer.rdbuf()->in_avail())
					continue ;
				_impl->state = DecodeTrailer;
			} else if (_impl->current_body_position < _impl->current_chunk_size + 2) {
				while (
					_impl->current_body_position < _impl->current_chunk_size
					&& _impl->input_buffer.rdbuf()->in_avail()
				) {
					_impl->decoded_body.put(_impl->input_buffer.get());
					++_impl->current_body_position;
				}
				if (!_impl->input_buffer.rdbuf()->in_avail())
					continue ;
				if (input == "\r") // single input case
					break ;
				if (checkCRLF())
					_impl->state = DecodeSize;
				else
					_impl->state = Error;
			}
		}
		if (_impl->state == DecodeTrailer) {
			size_t offset = _impl->input_buffer.tellg();
			std::string str = _impl->input_buffer.str().substr(offset);
			if (str.find("\r\n") == std::string::npos)
				break ;
			if (checkCRLF()) {
				_impl->state = Complete;
			} else {
				while (
					_impl->input_buffer.rdbuf()->in_avail()
				) {
					if (checkCRLF())
						break ;
					else
						_impl->input_buffer.get();
				}
			}
		}
	}
}

State ChunkedBody::getState() {
	return (_impl->state);
}

ChunkedBody::operator std::string() {
	return (_impl->decoded_body.str());
}
