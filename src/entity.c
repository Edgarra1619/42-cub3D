#include <cub3d/game.h>

static void	handle_entity_coll(t_vec2 cell, t_box box, t_scene *scene);

void	update_entities(t_scene *const scene, const float delta)
{
	const t_box	box = get_box(scene->player.pos, 0.5f);

	(void)delta;
	handle_entity_coll((t_vec2){box.ul.x, box.ul.y}, box, scene);
	handle_entity_coll((t_vec2){box.dr.x, box.ul.y}, box, scene);
	handle_entity_coll((t_vec2){box.ul.x, box.dr.y}, box, scene);
	handle_entity_coll((t_vec2){box.dr.x, box.dr.y}, box, scene);
}

static void	handle_entity_coll(
	const t_vec2 cell, const t_box box, t_scene *const scene)
{
	t_entity	*entity;

	if (!check_entity_coll(cell, box, scene))
		return ;
	entity = scene->entities + (scene->map[cell.x][cell.y] >> 2);
	if (entity->type == KEY)
	{
		scene->map[entity->pos.x][entity->pos.y] = SPACE;
		scene->entity_count--;
		scene->player.key_count++;
	}
	else if (entity->type == DOOR)
	{
		if (scene->player.key_count)
		{
			entity->unlocked = true;
			entity->open = true;
			scene->player.key_count--;
		}
	}
}
