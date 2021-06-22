/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Path.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 22:23:29 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/22 19:26:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Path.hpp"

Path::Path() : _is_directory(false), _is_empty(true), _len(0) {}
Path::~Path(){}

Path::Path(std::string path)
{
	_len = path.length();
	std::string segment;
	if (path.empty())
	{
		_is_empty = true;
		return ;
	}
	_is_empty = false;
	std::string::iterator it = path.begin();
	for (; it != path.end(); ++it)
	{
		if (*it == '/')
		{
			if (!segment.empty())
				_segments.push_back(segment);
			segment.clear();
		}
		else
			segment += *it;
	}
	if (!segment.empty())
		_segments.push_back(segment);
	--it;
	_is_directory = false;
	if (*it == '/')
		_is_directory = true;
}

Path::Path(const Path& other)
{
	_is_empty = other._is_empty;
	_is_directory = other._is_directory;
	_segments = other._segments;
	_len = other._len;
}

Path& Path::operator=(const Path& rhs)
{
	if (&rhs == this)
		return (*this);
	_is_empty = rhs._is_empty;
	_is_directory = rhs._is_directory;
	_segments = rhs._segments;
	_len = rhs._len;
	return (*this);
}

Path::iterator Path::begin()
{
	return (_segments.begin());
}

Path::iterator Path::end()
{
	return (_segments.end());
}

bool Path::empty()
{
	return (_is_empty);
}

void Path::setIsDirectory(bool b)
{
	++_len;
	_is_directory = b;
}

bool Path::directory()
{
	return (_is_directory);
}

void Path::setIsEmpty(bool b)
{
	_is_empty = b;
}

void Path::setSegments(cnt segments)
{
	_segments = segments;
}

void Path::addSegment(std::string segment)
{
	if (!segment.empty())
		_segments.push_back(segment);
}

bool Path::findSegment(Path prefix, Path::iterator& output_it)
{
	iterator path_it = _segments.begin();
	iterator prefix_it = prefix.begin();
	while (path_it != _segments.end() && prefix_it != prefix.end())
	{
		if (*path_it != *prefix_it)
			break ;
		++path_it;
		++prefix_it;
	}
	if (prefix_it == prefix.end())
	{
		output_it = path_it;
		return (true);
	}
	return (false);
}

size_t Path::length()
{
	return (_len);
}

std::string Path::toStr()
{
	if (_is_empty)
		return (std::string());
	std::string path;
	iterator it = _segments.begin();
	if (it != _segments.end() && *it == ".")
	{
		path += *it;
		++it;
	}
	for (; it != _segments.end(); ++it)
		path += '/' + *it;
	if (_is_directory)
		path += '/';
	return (path);
}
