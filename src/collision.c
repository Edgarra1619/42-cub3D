#include <cub3d/game.h>

static int	check_box_coll(t_box a, t_box b);

t_box	get_box(const t_vec2f pos, const float size)
{
	return ((t_box){
		{pos.x - size, pos.y - size},
		{pos.x + size, pos.y + size}
	});
}

static t_box	get_cell_box(const t_vec2 cell, const float size)
{
	return ((t_box){
		{cell.x + 0.5f - size, cell.y + 0.5f - size},
		{cell.x + 0.5f + size, cell.y + 0.5f + size}
	});
}

int	check_cell_coll(
	const t_vec2 cell, const t_box box, const t_scene *const scene)
{
	const char		cell_data = scene->map[cell.x][cell.y];
	const char		type = cell_data & 3;
	const t_entity	*entity;

	if (type == WALL)
		return (1);
	if (type == ENTITY)
	{
		entity = scene->entities + (cell_data >> 2);
		if (entity->type == DOOR && !entity->enabled)
			return (check_box_coll(box, get_cell_box(cell, 0.25f)));
	}
	return (0);
}

int	check_entity_coll(
	const t_vec2 cell, const t_box box, const t_scene *const scene)
{
	const char	cell_data = scene->map[cell.x][cell.y];
	const char	type = cell_data & 3;

	if (type == ENTITY)
		return (check_box_coll(box, get_cell_box(cell, 0.25f)));
	return (0);
}

static int	check_box_coll(const t_box a, const t_box b)
{
	return (a.dr.x >= b.ul.x && a.ul.x <= b.dr.x
		&& a.dr.y >= b.ul.y && a.ul.y <= b.dr.y);
}
