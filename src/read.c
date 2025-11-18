#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <cub3d/cub3d.h>

static inline void	skip_spaces(int fd);

char	read_char(const int fd, const bool peek)
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

int	read_value(const int fd, char *const dest, const int size)
{
	int		i;
	char	c;

	skip_spaces(fd);
	i = 0;
	while (true)
	{
		c = read_char(fd, true);
		if (c == ' ' || c == '\n' || c == EOF)
		{
			dest[i] = '\0';
			return (0);
		}
		if (i >= size - 1)
			return (1);
		dest[i++] = read_char(fd, false);
	}
}

int	read_line(const int fd, char *const dest, const int size)
{
	int		i;
	char	c;

	skip_spaces(fd);
	i = 0;
	while (true)
	{
		c = read_char(fd, false);
		if (c == '\n' || c == EOF)
		{
			dest[i] = '\0';
			return (0);
		}
		if (i >= size - 1)
			return (1);
		dest[i++] = c;
	}
}

static inline void	skip_spaces(const int fd)
{
	while (read_char(fd, true) == ' ')
		read_char(fd, false);
}
