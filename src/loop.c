#include <cub3d/cub3d.h>
#include <cub3d/defines.h>
#include <cub3d/types.h>
#include <cub3d/vector.h>

#include <libft.h>

#include <mlx.h>

void	update_dir(t_player *const player, const float delta)
{
	static const float	speed = 0.25f;
	const int			keys_held = player->keys_held;

	if (keys_held & KEYCODELEFT)
		player->dir_angle -= speed * delta;
	if (keys_held & KEYCODERIGHT)
		player->dir_angle += speed * delta;
	player->dir = angle_to_vec2f(player->dir_angle);
}

void	update_pos(t_player *const player, const float delta)
{
	const t_vec2f	dir = mult_vec2ff(player->dir, delta);
	const int		keys_held = player->keys_held;
	t_vec2f			pos;

	pos = player->pos;
	if (keys_held & KEYCODEW)
		pos = sum_vec2f(pos, (t_vec2f){-dir.x, -dir.y});
	if (keys_held & KEYCODES)
		pos = sum_vec2f(pos, dir);
	if (keys_held & KEYCODEA)
		pos = sum_vec2f(pos, (t_vec2f){-dir.y, dir.x});
	if (keys_held & KEYCODED)
		pos = sum_vec2f(pos, (t_vec2f){dir.y, -dir.x});
	player->pos = pos;
}

// INFO: returns 1 when interacting
char	treat_input(t_scene *const scene, const float delta)
{
	const int	keys_held = scene->player.keys_held;

	if (keys_held & (KEYCODELEFT | KEYCODERIGHT))
		update_dir(&scene->player, delta);
	if (keys_held & (KEYCODEW | KEYCODES | KEYCODEA | KEYCODED))
		update_pos(&scene->player, delta);
	return (keys_held & BUTTONL);
}

int	loop(t_data *data)
{
	treat_input(data->scene, 0.01f);
	ft_memset(data->minimap.buffer->data, 0xFF444444, data->minimap.buffer->width * data->minimap.buffer->height * sizeof(int));
	render_minimap(&(data->minimap), data->scene);
	mlx_put_image_to_window(data->display, data->window, data->minimap.buffer, 0, 0);
	return (0);
}
