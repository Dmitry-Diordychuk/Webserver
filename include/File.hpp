/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 01:36:51 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/29 05:58:56 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
#define FILE_HPP

#include "FDBuffer.hpp"
#include <stdexcept>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <ctime>

class File
{
private:
	int						_fd;
	bool					_is_open;
	bool					_was_created;
	std::string				_type;
	std::string				_last_mod_time;
	std::string				_path;

public:
	File();
	File(std::string path, bool read);
	~File();

	bool openFile(std::string path, bool read);
	void closeFile();
	bool isOpen();
	int getFD();
	std::string getContent();

	void writeToFile(std::string content);
	void deleteFile();

	std::string getType();
	std::string getLastModTime();
	bool wasCreated();
};

#endif // FILE_HPP
