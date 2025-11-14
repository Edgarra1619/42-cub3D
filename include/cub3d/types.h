#ifndef TYPES_H
# define TYPES_H

# ifndef MAP_MAX
#  define MAP_MAX 1024
# endif

# ifndef ENTITY_MAX
#  define ENTITY_MAX 64
# endif

# include <mlx_int.h>
# include <cub3d/vector.h>

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

typedef union u_color
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

enum e_entity : char
{
	door,
	key
};

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
	t_vec2		mouse_pos;
}	t_player;

typedef struct s_scene
{
	t_vec2		map_size;
	char		map[MAP_MAX][MAP_MAX];
	int			entity_count;
	t_entity	entities[ENTITY_MAX];
	t_player	player;
}	t_scene;

typedef struct s_data
{
	t_xvar		*display;
	t_win_list	*window;
	t_img		*buffer;
	t_scene		*scene;
}	t_data;

#endif
