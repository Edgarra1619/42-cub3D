#include <cub3d/cub3d.h>
#include <cub3d/strings.h>
#include <cub3d/render.h>
#include <cub3d/hooks.h>
#include <cub3d/parse.h>

#include <libft.h>

#include <mlx.h>

#include <errno.h>

static int	init_window(t_data *data);
static int	init_scene(t_scene *scene, const char *file, void *mlx);
static int	init_assets(t_scene *scene, int fd, void *mlx);
static int	init_map(t_scene *scene, int fd);

int	init(t_data *const data, const char *const file)
{
	data->display = mlx_init();
	return (!data->display
		|| init_scene(&data->scene, file, data->display)
		|| init_window(data));
}

static int	init_window(t_data *const data)
{
	data->window
		= mlx_new_window(data->display, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!data->window)
		return (1);
	data->buffer = mlx_new_image(data->display, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->buffer)
		return (1);
	data->minimap.buffer = data->buffer;
	data->minimap.pixel_size = 242 / (MINIMAP_SIZE * 2);
	mlx_hook(data->window, KeyPress, KeyPressMask,
		keyboard_down_hook, &(data->scene.player));
	mlx_hook(data->window, KeyRelease, KeyReleaseMask,
		keyboard_up_hook, data);
	mlx_hook(data->window, ClientMessage, LeaveWindowMask,
		mlx_loop_end, data->display);
	mlx_loop_hook(data->display, loop, data);
	mlx_mouse_move(data->display, data->window,
		WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_mouse_hide(data->display, data->window);
	return (0);
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
	return (parse_map(scene, fd) || validate_map(scene));
}
