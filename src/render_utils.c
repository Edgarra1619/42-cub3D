/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:29:33 by edgribei          #+#    #+#             */
/*   Updated: 2025/12/22 18:29:34 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d/types.h>

#include <libft.h>

void	draw_square(t_img *buffer, t_vec2 ul, t_vec2 dr, const t_color color)
{
	char *const	data = buffer->data;
	const int	width = buffer->width;
	int			tmp;

	ul.x = ft_max(ul.x, 0);
	ul.y = ft_max(ul.y, 0);
	dr.x = ft_min(dr.x, buffer->width);
	dr.y = ft_min(dr.y, buffer->height);
	tmp = ul.x;
	while (ul.y < dr.y)
	{
		ul.x = tmp;
		while (ul.x < dr.x)
		{
			((int *) data)[ul.x + ul.y * width] = color.color;
			ul.x++;
		}
		ul.y++;
	}
}

t_vec2f	world_to_camera(const t_player *const player, const t_vec2f pos)
{
	const t_vec2f	sprite_pos = (t_vec2f)
	{
		pos.x - player->pos.x,
		pos.y - player->pos.y
	};
	const float		matrix_helper = 1.0
		/ (player->cam_plane.x * player->dir.y
			- player->cam_plane.y * player->dir.x);

	return ((t_vec2f)
		{
			matrix_helper
			* (player->dir.y * sprite_pos.x - player->dir.x * sprite_pos.y),
			matrix_helper
			* (player->cam_plane.x * sprite_pos.y
				- player->cam_plane.y * sprite_pos.x)
		});
}
