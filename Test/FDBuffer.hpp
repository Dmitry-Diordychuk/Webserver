#include <cstdio>
#include <cstring>
#include <streambuf>
#include <unistd.h>

#define IN_BUFFER_SIZE 10

class FDBuffer : public std::streambuf
{
protected:
	int		_fd;
	char	_buffer[IN_BUFFER_SIZE];

public:
	FDBuffer(int fd);
	~FDBuffer();

	int_type underflow();
};
