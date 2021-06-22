/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 02:36:25 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/22 22:44:41 by kdustin          ###   ########.fr       */
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

bool cmpCaseInsensetive::operator()(const std::string& a, const std::string& b) const {
	std::string::const_iterator ita = a.begin();
	std::string::const_iterator itb = b.begin();
	for (; ita != a.end() && itb != b.end(); ++ita, ++itb)
	{
		if (std::tolower(*ita) != std::tolower(*itb))
			return (true);
	}
	if (ita != a.end() || itb != b.end())
		return (true);
	return (false);
}
