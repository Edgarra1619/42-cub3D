#ifndef DEFINES_H
# define DEFINES_H

# define READ_SIZE	1024
# define ERROR_MAX	1024
# define MAP_MAX	128
# define ENTITY_MAX	64

enum e_cell
{
	SPACE,
	WALL,
	ENTITY,
	PLAYER,
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
