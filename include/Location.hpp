/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:53:15 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/22 16:45:23 by kdustin          ###   ########.fr       */
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
	Path					_upload_directory;
	size_t					_max_body_size;

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
	void setUploadDirectory(std::string);
	void setMaxBodySize(size_t);

	std::string getIndex();
	std::string getPrefix();
	bool autoindex();
	std::string getUploadPath(Path request_path);
	size_t getMaxBodySize();

	Path checkLocation(Path path);
	bool checkAllowedMethods(Method method);
};

#endif // LOCATION_HPP
