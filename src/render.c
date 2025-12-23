/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:29:05 by edgribei          #+#    #+#             */
/*   Updated: 2025/12/22 18:29:06 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d/raycast.h>
#include <cub3d/vector.h>
#include <cub3d/types.h>
#include <cub3d/render.h>

static void	clear_upper_screen(const t_scene *const scene, t_img *const buffer)
{
	const t_vec2	buff_size = (t_vec2){buffer->width, buffer->height};
	float			dist_mult;
	t_color			color;
	t_vec2			i;

	i.y = 0;
	while (i.y < buff_size.y / 2)
	{
		color = scene->colors[CEILING_COL];
		dist_mult = 1.0 / (3 + ft_clampf(5 * ((float)(buffer->height / 2.0)
						/ (buffer->height / 2.0 - i.y) - 1), 1, 255));
		color.r = color.r * dist_mult;
		color.g = color.g * dist_mult;
		color.b = color.b * dist_mult;
		color.a = color.a * dist_mult;
		i.x = 0;
		while (i.x < buff_size.x)
			((int *)buffer->data)[i.x++ + i.y * buff_size.x] = color.color;
		i.y++;
	}
}

static void	clear_screen(const t_scene *const scene, t_img *const buffer)
{
	const t_vec2	buff_size = (t_vec2){buffer->width, buffer->height};
	float			dist_mult;
	t_color			color;
	t_vec2			i;

	clear_upper_screen(scene, buffer);
	i.y = buff_size.y;
	while (i.y > buff_size.y / 2)
	{
		color = scene->colors[FLOOR_COL];
		dist_mult = 1 / (3 + ft_clampf(5 * ((float)(buffer->height / 2.0)
						/ (i.y - buffer->height / 2.0) - 1), 1, 255));
		color.r = color.r * dist_mult;
		color.g = color.g * dist_mult;
		color.b = color.b * dist_mult;
		color.a = color.a * dist_mult;
		i.x = 0;
		while (i.x < buff_size.x)
			((int *)buffer->data)[i.x++ + i.y * buff_size.x] = color.color;
		i.y--;
	}
}

static void	render_column_loop(const t_scene *const scene,
							t_img *const buffer, const int col, t_rayhit hit)
{
	const float	dist_mult = 1
		/ (3 + ft_clampf(5 * (hit.proj_dist - 1), 1, 255));
	const int	height = buffer->height / hit.proj_dist;
	const int	start = buffer->height / 2 - height / 2;
	t_color		pixel;
	t_vec2		iter;

	if (!(hit.side_hit & 0b10))
		hit.hit_position.x = 1 - hit.hit_position.x;
	iter.x = ft_max(0, start);
	iter.y = ft_min(start + height, buffer->height);
	while (iter.x < iter.y)
	{
		pixel = ((t_color *)(scene->textures[hit.side_hit]->data
					+ (int)(scene->textures[hit.side_hit]->size_line
						* (int)((float)(iter.x - start) / height
							* scene->textures[hit.side_hit]->height))))
		[(int)(scene->textures[hit.side_hit]->width * hit.hit_position.x)];
		pixel.r = pixel.r * dist_mult;
		pixel.g = pixel.g * dist_mult;
		pixel.b = pixel.b * dist_mult;
		pixel.a = pixel.a * dist_mult;
		((int *)(buffer->data + buffer->size_line * iter.x))[col] = pixel.color;
		iter.x++;
	}
}

static void	render_column(const t_scene *const scene, t_data *const data,
						const t_vec2f dir, const int col)
{
	const t_rayhit	hit = cast_render_ray(scene, scene->player.pos, dir);

	data->zbuffer[col] = hit.proj_dist;
	render_column_loop(scene, data->buffer, col, hit);
}

void	render_camera(const t_scene *const scene, t_data *const data)
{
	const int		width = data->buffer->width;
	const t_vec2f	step
		= mult_vec2ff(scene->player.cam_plane, (float) 1 / (width));
	t_vec2f			dir;
	int				i;

	clear_screen(scene, data->buffer);
	dir = sum_vec2f(scene->player.dir,
			mult_vec2ff(scene->player.cam_plane, -1 / 2.0));
	i = 0;
	while (i < width)
	{
		render_column(scene, data, dir, i);
		dir = sum_vec2f(dir, step);
		i++;
	}
	render_sprites(scene, data);
}
