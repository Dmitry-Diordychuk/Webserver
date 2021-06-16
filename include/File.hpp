/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 01:36:51 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 02:46:42 by kdustin          ###   ########.fr       */
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

class File : public std::streambuf
{
private:
	int						_fd;
	std::vector<char_type> 	_buffer;
	bool					_is_open;

protected:
	virtual int underflow();

public:
	File();
	File(std::string path);
	~File();

	bool openFile(std::string path);
	void closeFile();
	bool isOpen();
	int getFD();
	std::string getContent();
};

#endif // FILE_HPP
