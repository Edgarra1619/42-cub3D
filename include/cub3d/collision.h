#ifndef COLLISION_H
# define COLLISION_H

# include <cub3d/types.h>
# include <cub3d/vector.h>

typedef struct s_box
{
	t_vec2f	ul;
	t_vec2f	dr;
}	t_box;

int	check_map_coll(t_vec2f pos, t_scene *scene);

#endif
