/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Method.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:10:28 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/12 02:12:42 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"

Method strToMethod(std::string str)
{
	if (str == "GET")
		return (GET);
	else if (str == "POST")
		return (POST);
	else if (str == "HEAD")
		return (HEAD);
	else if (str == "DELETE")
		return (DELETE);
	else
		return (ERR);
}
