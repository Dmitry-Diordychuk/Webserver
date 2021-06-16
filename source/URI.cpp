/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   URI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 19:08:26 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/12 14:36:56 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "URI.hpp"

URI::URI(){}
URI::~URI(){}

Path URI::getPath()
{
	return (_path);
}

void URI::setPath(Path path)
{
	_path = path;
}

size_t URI::length()
{
	return (_path.length() + _query.length());
}

void URI::setQuery(std::string params)
{
	_query = params;
}
