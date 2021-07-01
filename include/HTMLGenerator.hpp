/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTMLGenerator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:25:10 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/27 00:54:44 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HTMLGENERATOR_H__
#define __HTMLGENERATOR_H__

#include <string>
#include "Directory.hpp"

class HTMLGenerator
{
private:
	HTMLGenerator() {}
	~HTMLGenerator() {}
public:
	static std::string Autoindex(Directory *dir, std::string uri);
};

#endif // __HTMLGENERATOR_H__
