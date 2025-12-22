/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:13:10 by edgribei          #+#    #+#             */
/*   Updated: 2025/12/22 18:13:12 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include <cub3d/vector.h>

enum	e_side
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
};

typedef struct s_raycast_result
{
	t_vec2f		hit_position;
	enum e_side	side_hit;
	float		proj_dist;
}	t_rayhit;

struct s_rayhelper
{
	t_vec2	map_pos;
	t_vec2	map_step;
	t_vec2f	length_step;
	t_vec2f	length;
};

#endif
