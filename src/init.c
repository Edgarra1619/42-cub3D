#include <errno.h>
#include <libft.h>
#include <cub3d/cub3d.h>
#include <cub3d/strings.h>
#include <cub3d/parse.h>

#include <fcntl.h>

static int			init_assets(t_scene *scene, int fd, void *mlx);
static int			init_map(t_scene *scene, int fd);
static inline void		skip_empty_lines(int fd);

int	init_scene(t_scene *const scene, const char *const file, void *const mlx)
{
	const int	fd = open(file, O_RDONLY);

	if (fd == -1)
		return (print_error(SECT_INIT, NULL));
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

static inline void	skip_empty_lines(const int fd)
{
	while (read_char(fd, true) == '\n')
		read_char(fd, false);
}
