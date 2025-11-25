#include <cub3d/cub3d.h>
#include <cub3d/strings.h>
#include <cub3d/parse.h>

#include <libft.h>

static int	parse_cell(char cell, t_vec2 pos, t_scene *scene);
static int	parse_entity(char cell, t_vec2 pos, t_scene *scene);
static int	parse_player(char cell, t_vec2 pos, t_player *player);

int	parse_map(t_scene *const scene, const int fd)
{
	t_vec2	pos;
	char	cell;

	pos = (t_vec2){0};
	while (true)
	{
		cell = read_char(fd, false);
		if (cell == EOF)
			return (0);
		if (cell == '\n')
		{
			if (pos.x == 0)
				return (print_error(SECT_PARSE, ERR_MAP_LINE));
			scene->map_size
				= (t_vec2){ft_max(pos.x, scene->map_size.x), pos.y + 1};
			pos = (t_vec2){0, pos.y + 1};
			continue ;
		}
		if (pos.x >= MAP_MAX || pos.y >= MAP_MAX)
			return (print_error(SECT_PARSE, ERR_MAP_MAX));
		if (parse_cell(cell, pos, scene))
			return (1);
		pos.x++;
	}
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

static int	parse_entity(
	const char cell, const t_vec2 pos, t_scene *const scene)
{
	const int	id = scene->entity_count++;
	t_entity	entity;

	if (id >= ENTITY_MAX)
		return (print_error(SECT_PARSE, ERR_ENTITY_MAX));
	entity.type = get_entity_type(cell);
	entity.pos = pos;
	entity.open = false;
	entity.unlocked = false;
	scene->map[pos.x][pos.y] += (id << 2);
	scene->entities[id] = entity;
	return (0);
}

static int	parse_player(
	const char cell, const t_vec2 pos, t_player *const player)
{
	if (player->pos.x != -1.0f)
		return (print_error(SECT_PARSE, ERR_MUL_SPAWN));
	player->pos = (t_vec2f){pos.x + 0.5f, pos.y + 0.5f};
	if (cell == 'N')
		player->dir = (t_vec2f){0, 1};
	else if (cell == 'S')
		player->dir = (t_vec2f){0, -1};
	else if (cell == 'W')
		player->dir = (t_vec2f){-1, 0};
	else if (cell == 'E')
		player->dir = (t_vec2f){1, 0};
	return (0);
}
