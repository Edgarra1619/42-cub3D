/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:34:38 by vde-albu          #+#    #+#             */
/*   Updated: 2025/12/22 18:34:39 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d/vector.h>

#include <math.h>

t_vec2f	sum_vec2f(const t_vec2f a, const t_vec2f b)
{
	return ((t_vec2f){a.x + b.x, a.y + b.y});
}

t_vec2f	mult_vec2ff(const t_vec2f a, const float b)
{
	return ((t_vec2f){a.x * b, a.y * b});
}

t_vec2f	norm_vec2f(const t_vec2f vec)
{
	const float	mag = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));

	if (mag == 0)
		return (vec);
	return ((t_vec2f){vec.x / mag, vec.y / mag});
}

t_vec2f	rot_vec2ff(const t_vec2f a, const float b)
{
	return ((t_vec2f){
		cosf(b) * a.x - sinf(b) * a.y,
		sinf(b) * a.x + cosf(b) * a.y
	});
}

float	mag2_vec2f(const t_vec2f a)
{
	return (a.x * a.x + a.y * a.y);
}
