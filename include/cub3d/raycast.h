#ifndef RAYCAST_H
# define RAYCAST_H
# include <cub3d/vector.h>


typedef struct s_raycast_result
{
	t_vec2f	hit_position;
	enum
	{
		NORTH,
		EAST,
		SOUTH,
		WEST,
	} side_hit;
	float	projDist;
} t_rayhit;

struct s_rayhelper
{
	t_vec2	map_pos;
	t_vec2	map_step;
	t_vec2f	length_step;
	t_vec2f	length;
};

#endif
