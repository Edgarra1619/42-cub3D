#include <cub3d/types.h>
#include <cub3d/render.h>
#include <libft.h>
#include <cub3d/vector.h>
#include <mlx.h>
#include <mlx_int.h>

static int	get_celltype (t_scene *scene, t_vec2 pos)
{
	if (pos.x < 0 || pos.y < 0 ||
		pos.x >= scene->map_size.x || pos.y >= scene->map_size.y)
		return (1);
	return (scene->map[pos.x][pos.y]);
}

void	render_minimap (t_img *buffer, t_scene *scene)
{
	const t_vec2	center = (t_vec2) {scene->player.pos.x, scene->player.pos.y};
	const t_vec2f	offset = (t_vec2f) {scene->player.pos.x - center.x, scene->player.pos.y - center.y};
	t_vec2			current;
	const int		pixel_size = buffer->height / (MINIMAP_SIZE * 2);

	current.x = 0;
	while (current.x <= MINIMAP_SIZE * 2)
	{
		current.y = 0;
		while (current.y <= MINIMAP_SIZE * 2)
		{
			if (!get_celltype(scene,
					(t_vec2) {current.x - MINIMAP_SIZE + center.x,
						current.y - MINIMAP_SIZE + center.y}))
				draw_square(buffer,
					(t_vec2) {(current.x - offset.x) * pixel_size,
						(current.y - offset.y) * pixel_size},
					(t_vec2) {(current.x - offset.x + 1) * pixel_size,
						(current.y - offset.y + 1) * pixel_size},
					(t_color) 0x444444);
			current.y++;
		}
		current.x++;
	}
	draw_square(buffer,
		(t_vec2) {MINIMAP_SIZE * pixel_size - pixel_size/4,
			MINIMAP_SIZE * pixel_size - pixel_size/4},
		(t_vec2) {MINIMAP_SIZE * pixel_size + pixel_size/4,
			MINIMAP_SIZE * pixel_size + pixel_size/4},
		(t_color) GREEN);
}
