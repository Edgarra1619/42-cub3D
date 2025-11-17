#ifndef DEFINES_H
# define DEFINES_H

# ifndef READ_SIZE
#  define READ_SIZE		1024
# endif
# ifndef ERROR_MAX
#  define ERROR_MAX		1024
# endif
# ifndef MAP_MAX
#  define MAP_MAX		1024
# endif
# ifndef ENTITY_MAX
#  define ENTITY_MAX	64
# endif

//here for debugging purposes
enum	e_std_colors
{
	RED = 0xFFFF0000,
	GREEN = 0xFF00FF00,
	BLUE = 0xFF0000FF,
	YELLOW = 0xFFFFFF00,
	WHITE = 0xFFFFFFFF,
	BLACK = 0xFF000000,
};

enum	e_input
{
	KEYCODEW = 1 << 0,
	KEYCODES = 1 << 1,
	KEYCODEA = 1 << 2,
	KEYCODED = 1 << 3,
	KEYCODEQ = 1 << 4,
	KEYCODEE = 1 << 5,
	BUTTONL = 1 << 6,
	BUTTONR = 1 << 7,
};

#endif
