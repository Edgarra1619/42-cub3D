#include <cub3d/game.h>

static void	handle_entity_coll(t_vec2 cell, t_box box, t_scene *scene);

void	update_entities(t_scene *const scene, const float delta)
{
	const t_box	box = get_box(scene->player.pos, 0.5f);
	const int	entity_count = scene->entity_count;
	int			i;
	t_entity	*entity;

	handle_entity_coll((t_vec2){box.ul.x, box.ul.y}, box, scene);
	handle_entity_coll((t_vec2){box.dr.x, box.ul.y}, box, scene);
	handle_entity_coll((t_vec2){box.ul.x, box.dr.y}, box, scene);
	handle_entity_coll((t_vec2){box.dr.x, box.dr.y}, box, scene);
	i = 0;
	while (i < entity_count)
	{
		entity = scene->entities + i;
		i++;
		if (entity->type == DOOR)
		{
			if (!entity->open)
				continue ;
			if (entity->lock_time > delta)
				entity->lock_time -= delta;
			else
				entity->open = false;
		}
	}
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
		scene->player.key_count++;
	}
	else if (entity->type == DOOR)
	{
		if (entity->unlocked)
			entity->open = true;
		else if (scene->player.key_count > 0)
		{
			entity->unlocked = true;
			entity->open = true;
			scene->player.key_count--;
		}
		if (entity->open)
			entity->lock_time = 2000;
	}
}
