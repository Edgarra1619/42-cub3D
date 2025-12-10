#include <cub3d/cub3d.h>
#include <cub3d/strings.h>
#include <cub3d/render.h>
#include <cub3d/hooks.h>
#include <cub3d/parse.h>

#include <libft.h>

#include <mlx.h>

#include <errno.h>

static void	init_mlx(t_data *data);
static int	init_scene(t_scene *scene, const char *file, void *mlx);
static int	init_assets(t_scene *scene, int fd, void *mlx);
static int	init_map(t_scene *scene, int fd);

int	init(t_data *const data, const char *const file)
{
	init_mlx(data);
	return (init_scene(&data->scene, file, data->display));
}

// TODO: protect allocs
static void	init_mlx(t_data *const data)
{
	data->display = mlx_init();
	data->window = mlx_new_window(data->display, 512, 512, "cub3D");
	data->buffer = mlx_new_image(data->display, 512, 512);
	data->minimap.buffer = mlx_new_image(data->display, 242, 242);
	data->minimap.pixel_size
		= data->minimap.buffer->height / (MINIMAP_SIZE * 2);
	mlx_hook(data->window, ButtonPress, ButtonPressMask, mouse_down_hook,
		&(data->scene.player));
	mlx_hook(data->window, ButtonRelease, ButtonReleaseMask, mouse_up_hook,
		&(data->scene.player));
	mlx_hook(data->window, MotionNotify, ButtonMotionMask, mouse_move_hook,
		&(data->scene.player));
	mlx_hook(data->window, KeyPress, KeyPressMask, keyboard_down_hook,
		&(data->scene.player));
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, keyboard_up_hook,
		data);
	mlx_loop_hook(data->display, loop, data);
	mlx_hook(data->window, ClientMessage, LeaveWindowMask, mlx_loop_end,
		data->display);
}

static int	init_scene(
	t_scene *const scene, const char *const file, void *const mlx)
{
	const int	fd = open(file, O_RDONLY);
	const int	file_len = ft_strlen(file);

	if (fd == -1)
		return (print_error(SECT_INIT, NULL));
	if (file_len < 4 || ft_strcmp(".cub", file + file_len - 4))
		return (print_error(SECT_INIT, ERR_INV_FORMAT));
	if (init_assets(scene, fd, mlx) || init_map(scene, fd))
		return (1);
	close(fd);
	return (0);
}

static int	init_assets(t_scene *const scene, const int fd, void *const mlx)
{
	int	asset_count;

	errno = 0;
	asset_count = TEXTURE_COUNT + COLOR_COUNT;
	while (asset_count--)
	{
		skip_empty_lines(fd);
		if (parse_prop(scene, fd, mlx))
			return (1);
	}
	return (0);
}

static int	init_map(t_scene *const scene, const int fd)
{
	skip_empty_lines(fd);
	ft_memset(scene->map, WALL, sizeof(char) * MAP_MAX * MAP_MAX);
	scene->player.pos.x = -1.0f;
	if (parse_map(scene, fd) || validate_map(scene))
		return (1);
	return (0);
}
