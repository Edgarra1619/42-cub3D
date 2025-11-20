#include <cub3d/cub3d.h>
#include <cub3d/defines.h>
#include <cub3d/types.h>
#include <cub3d/vector.h>

#include <libft.h>

#include <mlx.h>

// INFO: returns 1 when interacting
char	treat_input(t_player *player, float delta)
{
	const char	interact = player->keys_held & BUTTONL;

	if (player->keys_held & KEYCODEW)
		player->pos.y -= 1 * delta;
	if (player->keys_held & KEYCODES)
		player->pos.y += 1 * delta;
	if (player->keys_held & KEYCODEA)
		player->pos.x -= 1 * delta;
	if (player->keys_held & KEYCODED)
		player->pos.x += 1 * delta;
	return (interact);
}

int	loop(t_data *data)
{
	treat_input(&data->scene->player, 0.01f);
	ft_memset(data->minimap.buffer->data, 0xFF444444, data->minimap.buffer->width * data->minimap.buffer->height * sizeof(int));
	render_minimap(&(data->minimap), data->scene);
	mlx_put_image_to_window(data->display, data->window, data->minimap.buffer, 0, 0);
	return (0);
}
