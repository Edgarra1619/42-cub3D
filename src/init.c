#include <libft.h>
#include <cub3d/cub3d.h>
#include <cub3d/strings.h>
#include <cub3d/parse.h>

int	init_scene(t_scene *const scene, const char *const file)
{
	const int	fd = open(file, O_RDONLY);

	if (fd == -1)
		return (print_error(SECT_INIT, NULL));
	ft_memset(scene->map, WALL, sizeof(char) * MAP_MAX * MAP_MAX);
	scene->player.pos.x = -1.0f;
	if (parse_map(scene, fd) || validate_map(scene))
		return (1);
	close(fd);
	return (0);
}
