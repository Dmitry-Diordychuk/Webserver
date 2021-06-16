/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:53:15 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/15 01:16:32 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "Path.hpp"
#include "Method.hpp"
#include <vector>

class Location
{
private:
	std::string				_server_name;
	Path					_prefix;
	Path					_root;
	std::string				_index;
	std::vector<Method>		_allowed_methods;
	bool					_autoindex;
	std::string				_cgi;

	Location();
public:
	Location(std::string prefix);
	~Location();

	void setRoot(std::string);
	void setIndex(std::string);
	void setAllowedMethods(std::vector<Method>);
	void setAutoindex(bool);
	void setCgi(std::string);
	void setServerName(std::string);

	std::string getIndex();
	std::string getPrefix();
	bool getAutoindex();

	Path checkLocation(Path path);
	bool checkAllowedMethods(Method method);
};

#endif // LOCATION_HPP
