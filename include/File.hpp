/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 01:36:51 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/22 18:17:24 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <stdexcept>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <cstdio>

class File : public std::streambuf
{
private:
	int						_fd;
	std::vector<char_type> 	_buffer;
	bool					_is_open;
	bool					_was_created;
	std::string				_type;
	std::string				_last_mod_time;
	std::string				_path;

protected:
	virtual int underflow();

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
