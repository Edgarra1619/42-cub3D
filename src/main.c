#include <cub3d/cub3d.h>
#include <cub3d/hooks.h>
#include <cub3d/types.h>
#include <cub3d/vector.h>
#include <cub3d/render.h>

#include <libft.h>

#include <mlx_int.h>
#include <mlx.h>

#include <unistd.h>

void	init_mlx(t_data *data)
{
	data->display = mlx_init();
	data->window = mlx_new_window(data->display, 512, 512, "testing");
	data->buffer = mlx_new_image(data->display, 512, 512);
	data->minimap.buffer = mlx_new_image(data->display, 242, 242);
	data->minimap.pixel_size = data->minimap.buffer->height / (MINIMAP_SIZE * 2);
	mlx_hook(data->window, ButtonPress, ButtonPressMask, mouse_down_hook,
		&(data->scene->player));
	mlx_hook(data->window, ButtonRelease, ButtonReleaseMask, mouse_up_hook,
		&(data->scene->player));
	mlx_hook(data->window, MotionNotify, ButtonMotionMask, mouse_move_hook,
		&(data->scene->player));
	mlx_hook(data->window, KeyPress, KeyPressMask, keyboard_down_hook,
		&(data->scene->player));
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, keyboard_up_hook,
		data);
	mlx_loop_hook(data->display, loop, data);
	mlx_hook(data->window, ClientMessage, LeaveWindowMask, mlx_loop_end,
		data->display);
}

void	clean_mlx(t_data *data)
{
	mlx_destroy_image(data->display, data->buffer);
	mlx_destroy_image(data->display, data->minimap.buffer);
	mlx_destroy_window(data->display, data->window);
	mlx_destroy_display(data->display);
	free(data->display);
}

int	main(int argc, char **argv)
{
	static t_scene	scene;
	t_data			data;

	if (argc != 2)
		return (1);
	init_scene(&scene, argv[1]);

	data.scene = &scene;
	init_mlx(&data);
	mlx_loop(data.display);
	clean_mlx(&data);
}
