#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <cub3d/cub3d.h>

char	read_char(int fd, bool peek)
{
	static char	buffer[READ_SIZE];
	static int	size;
	static int	pos;

	if (pos >= size)
	{
		size = read(fd, buffer, READ_SIZE);
		if (size <= 0)
			return (EOF);
		pos = 0;
	}
	if (peek)
		return (buffer[pos]);
	return (buffer[pos++]);
}
