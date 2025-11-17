#include <cub3d/cub3d.h>
#include <cub3d/strings.h>
#include <cub3d/parse.h>
#include <cub3d/hooks.h>

#include <libft.h>

#include <mlx_int.h>
#include <mlx.h>

#include <fcntl.h>

int	init_scene(t_scene *const scene, const char *const file)
{
	const int	fd = open(file, O_RDONLY);

	if (fd == -1)
		return (print_error(SECT_INIT, NULL));
	ft_bzero(scene, sizeof(t_scene));
	return (parse_map(scene, fd));
}

