/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:34:34 by vde-albu          #+#    #+#             */
/*   Updated: 2025/12/22 18:34:35 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d/vector.h>

t_vec2	sum_vec2(const t_vec2 a, const t_vec2 b)
{
	return ((t_vec2){a.x + b.x, a.y + b.y});
}

t_vec2	mult_vec2i(const t_vec2 a, const int b)
{
	return ((t_vec2){a.x * b, a.y * b});
}

float	mag2_vec2i(const t_vec2 a)
{
	return (a.x * a.x + a.y * a.y);
}
