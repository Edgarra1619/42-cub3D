/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:13:22 by edgribei          #+#    #+#             */
/*   Updated: 2025/12/22 18:16:14 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <cub3d/types.h>
# include <cub3d/raycast.h>

# ifndef MINIMAP_WIDTH
#  define MINIMAP_WIDTH 242
# endif
# ifndef MINIMAP_SIZE
#  define MINIMAP_SIZE 10
# endif

void		draw_square(t_img *buffer, t_vec2 ul, t_vec2 dr, t_color color);
t_vec2f		world_to_camera(const t_player *player, t_vec2f pos);
t_rayhit	cast_render_ray(const t_scene *scene,
				t_vec2f pos, t_vec2f dir);
void		render_sprites(const t_scene *scene, t_data *data);

#endif
