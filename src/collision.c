#include <cub3d/collision.h>

static t_box	get_box(t_vec2f pos, float size);
static t_box	get_cell_box(t_vec2 cell, float size);
static int		check_box_coll(t_box a, t_box b);
static int		check_cell_coll(t_box box, t_vec2 cell, const t_scene *scene);

int	check_map_coll(const t_vec2f pos, const t_scene *const scene)
{
	const t_box	box = get_box(pos, 0.25f);

	return (check_cell_coll(box, (t_vec2){box.ul.x, box.ul.y}, scene)
		|| check_cell_coll(box, (t_vec2){box.dr.x, box.dr.y}, scene)
		|| check_cell_coll(box, (t_vec2){box.ul.x, box.dr.y}, scene)
		|| check_cell_coll(box, (t_vec2){box.dr.x, box.ul.y}, scene));
}

static int	check_box_coll(const t_box a, const t_box b)
{
	return (a.dr.x >= b.ul.x && a.ul.x <= b.dr.x
		&& a.dr.y >= b.ul.y && a.ul.y <= b.dr.y);
}

static int	check_cell_coll(
	const t_box box, const t_vec2 cell, const t_scene *const scene)
{
	const char	cell_data = scene->map[cell.x][cell.y];
	const char	type = cell_data & 3;

	if (type == WALL)
		return (1);
	if (type == ENTITY)
		return (check_box_coll(box, get_cell_box(cell, 0.25f)));
	return (0);
}

static t_box	get_box(const t_vec2f pos, const float size)
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
