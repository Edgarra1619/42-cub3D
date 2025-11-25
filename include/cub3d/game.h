#ifndef GAME_H
# define GAME_H

# include <cub3d/types.h>

typedef struct s_box
{
	t_vec2f	ul;
	t_vec2f	dr;
}	t_box;

void	update_player_dir(t_player *player, float delta);
void	update_player_pos(t_scene *scene, float delta);
int		check_map_coll(t_vec2f pos, t_scene *scene);

#endif
