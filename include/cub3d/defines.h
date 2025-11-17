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

//here for testing purposes
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

enum e_cell
{
	SPACE,
	WALL,
	ENTITY,
	PLAYER
};

enum e_entity
{
	KEY,
	DOOR,
};

enum e_texture
{
	NORTH_WALL_TEX,
	EAST_WALL_TEX,
	SOUTH_WALL_TEX,
	WEST_WALL_TEX,
	KEY_TEX,
	DOOR_TEX,
	TEXTURE_COUNT,
};

enum e_color
{
	FLOOR_COL,
	CEILING_COL,
	COLOR_COUNT,
};

#endif
