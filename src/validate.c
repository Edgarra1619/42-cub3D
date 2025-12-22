/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:38:04 by vde-albu          #+#    #+#             */
/*   Updated: 2025/12/22 18:38:05 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d/cub3d.h>
#include <cub3d/strings.h>

static int	check_map_seal(const t_scene *scene);

int	validate_map(const t_scene *const scene)
{
	if (scene->map_size.x == 0 || scene->map_size.y == 0)
		return (print_error(SECT_INIT, ERR_MAP_EMPTY));
	if (scene->player.pos.x == -1.0f)
		return (print_error(SECT_INIT, ERR_NO_SPAWN));
	if (check_map_seal(scene))
		return (print_error(SECT_INIT, ERR_MAP_SEAL));
	return (0);
}

static int	check_map_seal(const t_scene *const scene)
{
	const t_vec2	map_size = scene->map_size;
	static char		map[MAP_MAX][MAP_MAX];
	static t_vec2	stack[MAP_MAX * MAP_MAX * 4];
	int				size;
	t_vec2			curr;

	stack[0] = (t_vec2){scene->player.pos.x - 0.5f, scene->player.pos.y - 0.5f};
	size = 1;
	while (size--)
	{
		curr = stack[size];
		if (curr.x < 0 || curr.x >= map_size.x
			|| curr.y < 0 || curr.y >= map_size.y)
			return (1);
		if (map[curr.x][curr.y] || scene->map[curr.x][curr.y] == WALL)
			continue ;
		map[curr.x][curr.y] = 1;
		stack[size++] = (t_vec2){curr.x - 1, curr.y};
		stack[size++] = (t_vec2){curr.x + 1, curr.y};
		stack[size++] = (t_vec2){curr.x, curr.y - 1};
		stack[size++] = (t_vec2){curr.x, curr.y + 1};
	}
	return (0);
}
