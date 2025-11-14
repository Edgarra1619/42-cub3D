#ifndef TYPES_H
# define TYPES_H

# include <mlx_int.h>
# include <cub3d/cub3d.h>
# include <cub3d/vector.h>

enum e_cell
{
	SPACE,
	WALL,
	ENTITY,
	EMPTY,
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

typedef union s_color
{
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	};
	unsigned int	color;
}	t_color;

// TODO: add entity-specific members
typedef struct s_entity
{
	enum e_entity	type;
	t_vec2			pos;
}	t_entity;

typedef struct s_player
{
	t_vec2f	pos;
	t_vec2f	dir;
	int		keys_held;
}	t_player;

typedef struct s_scene
{
	t_img		*textures[TEXTURE_COUNT];
	t_color		colors[COLOR_COUNT];
	t_vec2		map_size;
	char		map[MAP_MAX][MAP_MAX];
	int			entity_count;
	t_entity	entities[ENTITY_MAX];
	t_player	player;
}	t_scene;

#endif
