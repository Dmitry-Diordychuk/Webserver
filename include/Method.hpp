/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:05:51 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/12 02:11:30 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __METHODS_H__
#define __METHODS_H__

#include <string>

enum Method
{
	GET,
	HEAD,
	POST,
	DELETE,
	ERR
};

Method strToMethod(std::string str);

#endif // __METHODS_H__
