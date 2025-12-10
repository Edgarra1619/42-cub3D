#include <cub3d/defines.h>
#include <cub3d/render.h>

static void		render_cell(const t_minimap *minimap,
					const t_scene *scene, t_vec2 pos);
static char		get_cell(const t_scene *scene, t_vec2 pos);
static t_color	get_cell_color(const t_scene *scene, char cell);

void	render_minimap(t_minimap *const minimap, const t_scene *const scene)
{
	t_vec2	current;

	draw_square(minimap->buffer, (t_vec2) {0, 0}, (t_vec2) {242, 242}, (t_color) BLACK);
	minimap->center = (t_vec2){scene->player.pos.x, scene->player.pos.y};
	minimap->offset = (t_vec2f){scene->player.pos.x - minimap->center.x,
		scene->player.pos.y - minimap->center.y};
	current.x = 0;
	while (current.x <= MINIMAP_SIZE * 2 + 1)
	{
		current.y = 0;
		while (current.y <= MINIMAP_SIZE * 2 + 1)
		{
			render_cell(minimap, scene, current);
			current.y++;
		}
		current.x++;
	}
	draw_square(minimap->buffer,
		(t_vec2){MINIMAP_SIZE * minimap->pixel_size - minimap->pixel_size / 4,
		MINIMAP_SIZE * minimap->pixel_size - minimap->pixel_size / 4},
		(t_vec2){MINIMAP_SIZE * minimap->pixel_size + minimap->pixel_size / 4,
		MINIMAP_SIZE * minimap->pixel_size + minimap->pixel_size / 4},
		(t_color) BLUE);
}

static void	render_cell(const t_minimap *const minimap,
	const t_scene *const scene, const t_vec2 pos)
{
	const char	cell = get_cell(scene, (t_vec2){
			pos.x - MINIMAP_SIZE + minimap->center.x,
			pos.y - MINIMAP_SIZE + minimap->center.y});
	const char	type = cell & 3;

	if (type == WALL)
		return ;
	draw_square(minimap->buffer,
		(t_vec2){(pos.x - minimap->offset.x) * minimap->pixel_size,
		(pos.y - minimap->offset.y) * minimap->pixel_size},
		(t_vec2){(pos.x - minimap->offset.x + 1) * minimap->pixel_size,
		(pos.y - minimap->offset.y + 1) * minimap->pixel_size},
		get_cell_color(scene, cell));
}

static char	get_cell(const t_scene *const scene, const t_vec2 pos)
{
	if (pos.x < 0 || pos.y < 0
		|| pos.x >= scene->map_size.x || pos.y >= scene->map_size.y)
		return (WALL);
	return (scene->map[pos.x][pos.y]);
}

static t_color	get_cell_color(const t_scene *const scene, const char cell)
{
	const char		type = cell & 3;
	const t_entity	*entity;

	if (type == SPACE)
		return ((t_color)GRAY);
	if (type == WALL)
		return ((t_color)BLACK);
	entity = scene->entities + (cell >> 2);
	if (entity->type == KEY)
		return ((t_color)YELLOW);
	if (entity->open)
		return ((t_color)GRAY);
	if (entity->unlocked)
		return ((t_color)GREEN);
	return ((t_color)RED);
}
