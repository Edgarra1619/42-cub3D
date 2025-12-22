/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:33:17 by vde-albu          #+#    #+#             */
/*   Updated: 2025/12/22 18:35:08 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <cub3d/types.h>

typedef struct s_box
{
	t_vec2f	ul;
	t_vec2f	dr;
}	t_box;

void	update_player_dir(t_player *player, float delta);
void	update_player_dir_mouse(t_player *player, int mouse_x);
void	update_player_pos(t_scene *scene, float delta);
void	update_entities(t_scene *scene, float delta);
t_box	get_box(t_vec2f pos, float size);
int		check_cell_coll(t_vec2 cell, t_box box, const t_scene *scene);
int		check_entity_coll(t_vec2 cell, t_box box, const t_scene *scene);
int		update_mouse(t_data *data);

#endif
