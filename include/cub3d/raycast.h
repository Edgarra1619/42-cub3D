#ifndef RAYCAST_H
# define RAYCAST_H
# include <cub3d/vector.h>

enum	e_side
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
};

typedef struct s_raycast_result
{
	t_vec2f		hit_position;
	enum e_side	side_hit;
	float		proj_dist;
}	t_rayhit;

struct s_rayhelper
{
	t_vec2	map_pos;
	t_vec2	map_step;
	t_vec2f	length_step;
	t_vec2f	length;
};

#endif
