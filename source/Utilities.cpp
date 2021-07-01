/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 02:36:25 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/29 06:29:58 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utilities.hpp"

std::string convertNumtoStr(size_t val)
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

bool mapCmpCaseInsensetive::operator()(const std::string& a, const std::string& b) const {
	std::string la;
	std::string lb;
	std::string::const_iterator it = a.begin();
	for (; it != a.end(); ++it)
		la += std::tolower(*it);
	it = b.begin();
	for (; it != b.end(); ++it)
		lb += std::tolower(*it);
	return (std::lexicographical_compare(la.begin(), la.end(), lb.begin(), lb.end()));
}
