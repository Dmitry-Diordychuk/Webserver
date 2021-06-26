/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 02:35:09 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/23 15:19:58 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <sstream>
#include <functional>
#include <algorithm>

std::string intToStr(size_t val);
std::string trim(std::string str);

struct mapCmpCaseInsensetive {
	bool operator()(const std::string& a, const std::string& b) const;
};

#endif // UTILITIES_HPP
