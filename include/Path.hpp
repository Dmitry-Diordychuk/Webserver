/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Path.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 22:17:07 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/13 03:01:15 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PATH_H__
#define __PATH_H__

#include <string>
#include <vector>

class Path
{
public:
	typedef std::vector<std::string>			cnt;
	typedef std::vector<std::string>::iterator	iterator;

private:
	bool										_is_directory;
	bool										_is_empty;
	cnt											_segments;
	size_t										_len;

public:
	Path();
	Path(std::string path);
	Path(const Path& other);
	Path& operator=(const Path& rhs);
	~Path();

	iterator begin();
	iterator end();

	bool		empty();

	void		setIsEmpty(bool b);
	void		setIsDirectory(bool b);
	void		setSegments(cnt segments);
	void		addSegment(std::string segment);
	bool		findSegment(Path path, Path::iterator& output_it);
	size_t		length();
	std::string	toStr();
};

#endif // __PATH_H__
