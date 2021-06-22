/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 02:35:09 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/22 22:15:42 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <sstream>
#include <functional>

std::string intToStr(size_t val);
std::string trim(std::string str);

struct cmpCaseInsensetive {
	bool operator()(const std::string& a, const std::string& b) const;
};

#endif // UTILITIES_HPP
