/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Desc.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 23:12:05 by kdustin           #+#    #+#             */
/*   Updated: 2021/06/16 17:24:08 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DESC_H__
#define __DESC_H__

#include <poll.h>
#include <vector>
#include "Task.hpp"

enum Type {
	LISTEN,
	REQUEST,
	TASK
};

class Desc
{
private:
	std::vector<pollfd>	_descriptors;
	std::vector<Type>	_type;
	std::vector<Task>	_tasks;

public:
	Desc();
	~Desc();

	bool	readyToRead(size_t index);
	bool	readyToWrite(size_t index);
	int		getFD(size_t index);
	Type	getType(size_t index);
	Task	getTask(size_t index);

	pollfd *getPollfdSet();
	void addDesc(int fd, Type type);
	void addDesc(Task task);
	void delDesc(size_t index);

	size_t size();
};

#endif // __DESC_H__
