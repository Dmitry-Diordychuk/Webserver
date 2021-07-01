/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Path.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 22:17:07 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/29 22:39:27 by kdustin          ###   ########.fr       */
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
	bool		directory();
	void		setSegments(cnt segments);
	void		addSegment(std::string segment);
	bool		findSegment(Path path, Path::iterator& output_it);
	size_t		length();
	operator 	std::string();
};

#endif // __PATH_H__
