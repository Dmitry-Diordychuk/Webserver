
#include <fcntl.h>
#include "InBufFD.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc < 2)
		return (-1);
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	InBufFD ib(fd);
	std::istream in(&ib);

	std::string result;
	char c;
	while (in.get(c))
		result += c;

	std::cout << result << std::endl;
	close(fd);
}
