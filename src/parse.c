#include <stdio.h>
#include <fcntl.h>
#include <libft.h>
#include <cub3d/cub3d.h>
#include <cub3d/parse.h>
#include <cub3d/strings.h>

static char	get_cell_type(const char cell)
{
	if (cell == '0')
		return (SPACE);
	if (cell == '1' || cell == ' ')
		return (WALL);
	if (cell == 'K' || cell == '|' || cell == '-')
		return (ENTITY);
	if (cell == 'N' || cell == 'E' || cell == 'S' || cell == 'W')
		return (PLAYER);
	return (-1);
}

static char	get_entity_type(const char cell)
{
	if (cell == 'K')
		return (KEY);
	if (cell == '|' || cell == '-')
		return (DOOR);
	return (-1);
}

static int	parse_player(
	const char cell, const t_vec2 pos, t_player *const player)
{
	t_vec2f	dir;

	if (player->pos.x)
		return (print_error(SECT_PARSE, ERR_MUL_SPAWN));
	if (cell == 'N')
		dir = (t_vec2f){0, 1.0f};
	else if (cell == 'E')
		dir = (t_vec2f){1.0f, 0};
	else if (cell == 'S')
		dir = (t_vec2f){0, -1.0f};
	else
		dir = (t_vec2f){-1.0f, 0};
	player->pos = (t_vec2f){pos.x + 0.5f, pos.y + 0.5f};
	player->dir = dir;
	player->keys_held = 0;
	return (0);
}

static int	parse_entity(
	const char cell, const t_vec2 pos, t_scene *const scene)
{
	const int	id = scene->entity_count++;
	t_entity	entity;

	if (id >= ENTITY_MAX)
		return (print_error(SECT_PARSE, ERR_ENTITY_MAX));
	entity.type = get_entity_type(cell);
	entity.pos = pos;
	scene->map[pos.x][pos.y] += (id << 2);
	scene->entities[id] = entity;
	return (0);
}

static int	parse_cell(
	const char cell, const t_vec2 pos, t_scene *const scene)
{
	const char	type = get_cell_type(cell);

	if (type == -1)
		return (print_error(SECT_PARSE, ERR_INV_CELL));
	if (type == PLAYER)
	{
		scene->map[pos.x][pos.y] = SPACE;
		return (parse_player(cell, pos, &scene->player));
	}
	scene->map[pos.x][pos.y] = type;
	if (type == ENTITY)
		return (parse_entity(cell, pos, scene));
	return (0);
}

int	parse_map(t_scene *const scene, const int fd)
{
	t_vec2	pos;
	char	cell;

	ft_memset(scene->map, WALL, MAP_MAX * MAP_MAX);
	pos = (t_vec2){0};
	while (true)
	{
		cell = read_char(fd, false);
		if (cell == EOF)
			return (0);
		if (pos.x >= MAP_MAX || pos.y >= MAP_MAX)
			return (print_error(SECT_PARSE, ERR_MAP_MAX));
		if (cell == '\n')
		{
			if (pos.x == 0)
				return (print_error(SECT_PARSE, ERR_EMPTY_LINE));
			scene->map_size
				= (t_vec2){ft_max(pos.x, scene->map_size.x), pos.y + 1};
			pos = (t_vec2){0, pos.y + 1};
			continue ;
		}
		if (parse_cell(cell, pos, scene))
			return (1);
		pos.x++;
	}
}
