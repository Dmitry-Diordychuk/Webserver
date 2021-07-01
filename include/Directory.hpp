/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directory.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:20:42 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/30 22:17:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

#include <dirent.h>
#include <stdexcept>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>

class Directory
{
private:
	DIR				*_dir;
	struct dirent	*_ent;
	bool			_is_open;
	std::string		_path;
	bool			_is_dir;

public:
	Directory();
	Directory(std::string path);
	~Directory();

	void open(std::string path);
	std::string getNextName();
	bool isDir();
	bool isOpen();
	std::string getPath();

	static bool str_is_dir(std::string path);
};

#endif // __DIRECTORY_H__
