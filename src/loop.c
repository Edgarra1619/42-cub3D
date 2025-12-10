#include <cub3d/cub3d.h>
#include <cub3d/game.h>

#include <libft.h>

#include <mlx.h>

#include <sys/time.h>

static void		game_loop(t_scene *scene);
static void		render_loop(t_data *data);
static float	get_delta(void);

int	loop(t_data *const data)
{
	game_loop(&data->scene);
	render_loop(data);
	return (0);
}

static void	render_loop(t_data *const data)
{
	ft_bzero(data->minimap.buffer->data, sizeof(int)
		* data->minimap.buffer->width * data->minimap.buffer->height);
	render_camera(&data->scene, data->buffer);
	render_minimap(&(data->minimap), &data->scene);
	mlx_put_image_to_window(data->display, data->window,
		data->buffer, 0, 0);
}

static void	game_loop(t_scene *const scene)
{
	const float	delta = get_delta();
	const int	keys_held = scene->player.keys_held;

	if (keys_held & (KEYCODELEFT | KEYCODERIGHT))
		update_player_dir(&scene->player, delta);
	if (keys_held & (KEYCODEW | KEYCODES | KEYCODEA | KEYCODED))
		update_player_pos(scene, delta);
}

static float	get_delta(void)
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
