#include <cub3d/game.h>

static t_box	get_box(t_vec2f pos, float size);
static t_box	get_cell_box(t_vec2 cell, float size);
static int		check_box_coll(t_box a, t_box b);
static int		check_cell_coll(t_box box, t_vec2 cell, t_scene *scene);
static int		handle_entity_coll(char entity_id, t_scene *scene);

int	check_map_coll(const t_vec2f pos, t_scene *const scene)
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
	const t_box box, const t_vec2 cell, t_scene *const scene)
{
	const char	cell_data = scene->map[cell.x][cell.y];
	const char	type = cell_data & 3;

	if (type == WALL)
		return (1);
	if (type == ENTITY && check_box_coll(box, get_cell_box(cell, 0.25f)))
		return (handle_entity_coll(cell_data >> 2, scene));
	return (0);
}

// INFO: returns 1 on solid
static int	handle_entity_coll(const char entity_id, t_scene *const scene)
{
	t_entity *const	entity = scene->entities + entity_id;
	const char		type = entity->type;

	if (type == KEY)
	{
		scene->map[entity->pos.x][entity->pos.y] = SPACE;
		scene->entity_count--;
		scene->player.key_count++;
		return (0);
	}
	if (scene->player.key_count)
	{
		entity->unlocked = true;
		entity->open = true;
		scene->player.key_count--;
	}
	return (!entity->open);
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
