/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directory.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:20:42 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 02:50:33 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

#include <dirent.h>
#include <stdexcept>
#include <string>

class Directory
{
private:
	DIR				*_dir;
	struct dirent	*_ent;
	bool			_is_open;

public:
	Directory();
	Directory(std::string path);
	~Directory();

	void open(std::string path);
	std::string getNextName();
	bool isOpen();
	int getFD();
};

#endif // __DIRECTORY_H__
