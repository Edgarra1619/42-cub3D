#include <cub3d/vector.h>
#include <cub3d/types.h>
#include <mlx.h>
#include <X11/keysym.h>

//needs to receive t_data to close the loop
int	keyboard_up_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->display);
	if (keycode == 'w')
		data->scene->player.keys_held &= ~KEYCODEW;
	if (keycode == 's')
		data->scene->player.keys_held &= ~KEYCODES;
	if (keycode == 'a')
		data->scene->player.keys_held &= ~KEYCODEA;
	if (keycode == 'd')
		data->scene->player.keys_held &= ~KEYCODED;
	if (keycode == 'q')
		data->scene->player.keys_held &= ~KEYCODEQ;
	if (keycode == 'e')
		data->scene->player.keys_held &= ~KEYCODEE;
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
	return (0);
}

int	mouse_up_hook(int button, t_vec3 pos, t_player *player)
{
	(void) pos;
	if (button == 1)
		player->keys_held &= ~BUTTONL;
	else if (button == 3)
		player->keys_held &= ~BUTTONR;
	return (0);
}

int	mouse_down_hook(int button, t_vec3 pos, t_player *player)
{
	if (button == 1)
		player->keys_held |= BUTTONL;
	else if (button == 3)
		player->keys_held |= BUTTONR;
	player->mouse_pos = (t_vec2){pos.x, pos.z};
	return (0);
}

int	mouse_move_hook(int x, int y, t_player *player)
{
	// const t_vecf2	mov = (t_vecf2)
	// {(float)(state->mouse_pos.x - pos.x) / 10,
	// 	(float)(state->mouse_pos.y - pos.y) / 10};

	// rotate_camera(player->camera, mov);
	player->mouse_pos = (t_vec2){x, y};
	return (0);
}
