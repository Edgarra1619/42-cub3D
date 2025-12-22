/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:42:44 by edgribei          #+#    #+#             */
/*   Updated: 2025/12/22 18:44:05 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d/vector.h>
#include <cub3d/types.h>
#include <cub3d/render.h>

#include <mlx.h>

#include <X11/keysym.h>

// INFO: needs to receive t_data to close the loop
int	keyboard_up_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->display);
	if (keycode == 'w')
		data->scene.player.keys_held &= ~KEYCODEW;
	if (keycode == 's')
		data->scene.player.keys_held &= ~KEYCODES;
	if (keycode == 'a')
		data->scene.player.keys_held &= ~KEYCODEA;
	if (keycode == 'd')
		data->scene.player.keys_held &= ~KEYCODED;
	if (keycode == 'q')
		data->scene.player.keys_held &= ~KEYCODEQ;
	if (keycode == 'e')
		data->scene.player.keys_held &= ~KEYCODEE;
	if (keycode == XK_Left)
		data->scene.player.keys_held &= ~KEYCODELEFT;
	if (keycode == XK_Right)
		data->scene.player.keys_held &= ~KEYCODERIGHT;
	return (0);
}

int	keyboard_down_hook(int keycode, t_player *player)
{
	if (keycode == 'w')
		player->keys_held |= KEYCODEW;
	if (keycode == 's')
		player->keys_held |= KEYCODES;
	if (keycode == 'a')
		player->keys_held |= KEYCODEA;
	if (keycode == 'd')
		player->keys_held |= KEYCODED;
	if (keycode == 'q')
		player->keys_held |= KEYCODEQ;
	if (keycode == 'e')
		player->keys_held |= KEYCODEE;
	if (keycode == XK_Left)
		player->keys_held |= KEYCODELEFT;
	if (keycode == XK_Right)
		player->keys_held |= KEYCODERIGHT;
	return (0);
}

int	update_mouse(t_data *const data)
{
	static const t_vec2	origin = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
	t_vec2				pos;

	mlx_mouse_get_pos(data->display, data->window, &pos.x, &pos.y);
	if (pos.x != origin.x || pos.y != origin.y)
	{
		mlx_mouse_move(data->display, data->window, origin.x, origin.y);
		return (pos.x - origin.x);
	}
	return (0);
}
