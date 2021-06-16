/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTMLGenerator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:25:10 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 14:34:21 by kdustin          ###   ########.fr       */
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
	static std::string Autoindex(Directory dir);
};

#endif // __HTMLGENERATOR_H__
