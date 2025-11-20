#include <cub3d/defines.h>
#include <cub3d/types.h>
#include <cub3d/render.h>
#include <cub3d/vector.h>

#include <libft.h>

#include <mlx_int.h>
#include <mlx.h>

static int	get_celltype (t_scene *scene, t_vec2 pos)
{
	if (pos.x < 0 || pos.y < 0 ||
		pos.x >= scene->map_size.x || pos.y >= scene->map_size.y)
		return (WALL);
	return (scene->map[pos.x][pos.y]);
}

static void	render_cell(t_minimap *minimap, t_scene *scene, t_vec2 pos)
{
	const int	type = get_celltype(scene,
			(t_vec2) {pos.x - MINIMAP_SIZE + minimap->center.x,
					pos.y - MINIMAP_SIZE + minimap->center.y});

	if ((type & 0b00000011) == WALL)
		draw_square(minimap->buffer,
			(t_vec2) {(pos.x - minimap->offset.x) * minimap->pixel_size,
				(pos.y - minimap->offset.y) * minimap->pixel_size},
			(t_vec2) {(pos.x - minimap->offset.x + 1) * minimap->pixel_size,
				(pos.y - minimap->offset.y + 1) * minimap->pixel_size},
			(t_color) 0);
	if ((type & 0b00000011) == ENTITY)
		draw_square(minimap->buffer,
			(t_vec2) {(pos.x - minimap->offset.x) * minimap->pixel_size,
				(pos.y - minimap->offset.y) * minimap->pixel_size},
			(t_vec2) {(pos.x - minimap->offset.x + 1) * minimap->pixel_size,
				(pos.y - minimap->offset.y + 1) * minimap->pixel_size},
			(t_color) RED);
}

void	render_minimap (t_minimap *minimap, t_scene *scene)
{
	t_vec2	current;

	minimap->center = (t_vec2) {scene->player.pos.x, scene->player.pos.y};
	minimap->offset = (t_vec2f) {scene->player.pos.x - minimap->center.x, scene->player.pos.y - minimap->center.y};
	current.x = -1;
	while (current.x <= MINIMAP_SIZE * 2 + 1)
	{
		current.y = -1;
		while (current.y <= MINIMAP_SIZE * 2 + 1)
		{
			render_cell(minimap, scene, current);
			current.y++;
		}
		current.x++;
	}
	draw_square(minimap->buffer,
		(t_vec2) {MINIMAP_SIZE * minimap->pixel_size - minimap->pixel_size/4,
			MINIMAP_SIZE * minimap->pixel_size - minimap->pixel_size/4},
		(t_vec2) {MINIMAP_SIZE * minimap->pixel_size + minimap->pixel_size/4,
			MINIMAP_SIZE * minimap->pixel_size + minimap->pixel_size/4},
		(t_color) GREEN);
}
