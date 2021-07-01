/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   URI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:48:06 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/29 22:39:37 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __URI_H__
#define __URI_H__

#include "Path.hpp"

#include <string>
#include <list>
#include <utility>

class URI
{
private:
	// std::string	_scheme;
	// std::string	_authority;
	Path		_path;
	std::string	_query;

public:
	URI();
	~URI();

	Path getPath();

	void	setPath(Path path);
	void	setQuery(std::string params);
	size_t	length();
};

#endif // __URI_H__
