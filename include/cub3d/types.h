#ifndef TYPES_H
# define TYPES_H

# include <cub3d/defines.h>
# include <cub3d/vector.h>

# include <mlx_int.h>

# include <stdbool.h>

typedef union s_color
{
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	};
	int				color;
	unsigned int	ucolor;
}	t_color;

typedef struct s_entity
{
	enum e_entity	type;
	t_vec2			pos;
	bool			open;
	bool			unlocked;
}	t_entity;

typedef struct s_player
{
	t_vec2f	pos;
	t_vec2f	dir;
	int		keys_held;
	t_vec2	mouse_pos;
	int		key_count;
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

typedef struct s_minimap
{
	t_img	*buffer;
	t_vec2	center;
	t_vec2f	offset;
	int		pixel_size;
}	t_minimap;

typedef struct s_data
{
	t_xvar		*display;
	t_win_list	*window;
	t_img		*buffer;
	t_scene		scene;
	t_minimap	minimap;
}	t_data;

#endif
