/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 02:36:25 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/09 14:15:04 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utilities.hpp"

std::string intToStr(size_t val)
{
	std::stringstream convert;
	convert << val;
	return (convert.str());
}

std::string trim(std::string str)
{
	size_t i = 0;
	while (isspace(str[i]) && str[i] != '\0')
		++i;
	size_t j = 0;
	while (str[j] != '\0')
		++j;
	while (isspace(str[j]) && j > 0)
		++j;
	return (str.substr(i, j - i));
}
