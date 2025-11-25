#include <cub3d/cub3d.h>
#include <cub3d/defines.h>
#include <cub3d/types.h>
#include <cub3d/vector.h>
#include <cub3d/collision.h>

#include <libft.h>

#include <mlx.h>

#include <sys/time.h>

void	update_dir(t_player *const player, const float delta)
{
	static const float	speed = 0.005f;
	const int			keys_held = player->keys_held;
	float				theta;

	theta = 0;
	if (keys_held & KEYCODELEFT)
		theta -= speed * delta;
	if (keys_held & KEYCODERIGHT)
		theta += speed * delta;
	player->dir = rot_vec2ff(player->dir, theta);
}

t_vec2f	get_target_dir(t_player *const player)
{
	const t_vec2f	dir = player->dir;
	const int		keys_held = player->keys_held;
	t_vec2f			target_dir;

	target_dir = (t_vec2f){0};
	if (keys_held & KEYCODEW)
		target_dir = sum_vec2f(target_dir, (t_vec2f){-dir.x, -dir.y});
	if (keys_held & KEYCODES)
		target_dir = sum_vec2f(target_dir, dir);
	if (keys_held & KEYCODEA)
		target_dir = sum_vec2f(target_dir, (t_vec2f){-dir.y, dir.x});
	if (keys_held & KEYCODED)
		target_dir = sum_vec2f(target_dir, (t_vec2f){dir.y, -dir.x});
	return (norm_vec2f(target_dir));
}

void	update_pos(t_scene *const scene, const float delta)
{
	static const float	speed = 0.005f;
	const t_vec2f		pos = scene->player.pos;
	const t_vec2f		target_dir = get_target_dir(&scene->player);
	const t_vec2f		target_pos
		= sum_vec2f(pos, mult_vec2ff(target_dir, speed * delta));

	if (!check_map_coll((t_vec2f){target_pos.x, pos.y}, scene))
		scene->player.pos.x = target_pos.x;
	if (!check_map_coll((t_vec2f){pos.x, target_pos.y}, scene))
		scene->player.pos.y = target_pos.y;
}

// INFO: returns 1 when interacting
char	treat_input(t_scene *const scene, const float delta)
{
	const int	keys_held = scene->player.keys_held;

	if (keys_held & (KEYCODELEFT | KEYCODERIGHT))
		update_dir(&scene->player, delta);
	if (keys_held & (KEYCODEW | KEYCODES | KEYCODEA | KEYCODED))
		update_pos(scene, delta);
	return (keys_held & BUTTONL);
}

float	get_delta(void)
{
	static struct timeval	last_tv;
	struct timeval			tv;
	unsigned long long		delta_usec;

	if (!last_tv.tv_sec && !last_tv.tv_usec)
	{
		gettimeofday(&last_tv, NULL);
		return (0);
	}
	gettimeofday(&tv, NULL);
	delta_usec = (tv.tv_sec - last_tv.tv_sec) * 1000000
		+ tv.tv_usec - last_tv.tv_usec;
	last_tv = tv;
	return (delta_usec / 1000.0f);
}

int	loop(t_data *data)
{
	treat_input(data->scene, get_delta());
	ft_memset(data->minimap.buffer->data, 0xFF444444, data->minimap.buffer->width * data->minimap.buffer->height * sizeof(int));
	render_minimap(&(data->minimap), data->scene);
	mlx_put_image_to_window(data->display, data->window, data->minimap.buffer, 0, 0);
	return (0);
}
