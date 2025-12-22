/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:29:16 by edgribei          #+#    #+#             */
/*   Updated: 2025/12/22 18:29:18 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d/vector.h>
#include <cub3d/defines.h>
#include <cub3d/types.h>
#include <cub3d/render.h>

#include <libft.h>

#include <stdbool.h>

void	sort_sprites(int *const order,
			const float *const distance, const int count);

static void	fill_sprite_distance(const t_scene *const scene,
				const int *const order, float *const distance, const int count)
{
	int	i;
	int	tmp;

	i = count;
	while (--i >= 0)
	{
		tmp = order[i];
		distance[tmp] = mag2_vec2f((t_vec2f)
			{scene->player.pos.x - scene->entities[tmp].pos.x,
				scene->player.pos.y - scene->entities[tmp].pos.y});
	}
}

static void	render_column_loop(t_data *const data,
				const int tex_col, const int buffer_col, const float dist)
{
	const float	dist_mult = 1 / (3 + ft_clampf(5 * (dist - 1), 1, 255));
	const int	height = data->buffer->height / dist;
	const int	start = data->buffer->height / 2 - height / 2;
	t_color		pixel;
	t_vec2		iter;

	iter.x = ft_max(0, start) - 1;
	iter.y = ft_min(start + height, data->buffer->height);
	while (++iter.x < iter.y)
	{
		pixel = ((t_color *)(data->scene.textures[KEY_TEX]->data
					+ (int)(data->scene.textures[KEY_TEX]->size_line
						* (int)((float)(iter.x - start) / height
							* data->scene.textures[KEY_TEX]->height))))
		[(int)(tex_col)];
		if (pixel.a != 0)
			continue ;
		pixel.r = pixel.r * dist_mult;
		pixel.g = pixel.g * dist_mult;
		pixel.b = pixel.b * dist_mult;
		pixel.a = pixel.a * dist_mult;
		((int *)(data->buffer->data + data->buffer->size_line * iter.x))
		[buffer_col] = pixel.color;
	}
}

static void	fill_sprite_entities(const t_scene *const scene,
				int *const order, int *const count)
{
	int	i;

	*count = 0;
	i = scene->entity_count;
	while (--i >= 0)
	{
		if (scene->entities[i].type != KEY)
			continue ;
		order[(*count)++] = i;
	}
}

static void	render_sprite(const t_entity *const entity,
				const t_player *const player, t_data *const data,
				const int animation_frame)
{
	const t_vec2f	proj
		= world_to_camera(player,
			(t_vec2f){entity->pos.x + 0.5f, entity->pos.y + 0.5f});
	const int		pos = (float)(data->buffer->width / 2.0)
		* (1 + proj.x / proj.y * WINDOW_WIDTH / WINDOW_HEIGHT);
	const int		size = data->buffer->height / proj.y;
	const int		start = pos - size / 2;
	int				i;

	i = ft_min(size, data->buffer->width - start);
	while (i > 0 && i > -start)
	{
		if (proj.y < data->zbuffer[start + i])
			render_column_loop(data,
				data->scene.textures[KEY_TEX]->height
				* (animation_frame + ((float) i / size)), start + i, proj.y);
		i--;
	}
}

void	render_sprites(const t_scene *const scene, t_data *const data)
{
	static bool		filled = false;
	static int		entity_order[ENTITY_MAX];
	static int		count;
	float			entity_distance[ENTITY_MAX];
	int				i;

	if (!filled)
		fill_sprite_entities(scene, entity_order, &count);
	fill_sprite_distance(scene, entity_order, entity_distance, count);
	sort_sprites(entity_order, entity_distance, count);
	filled = true;
	i = count;
	while (--i >= 0)
	{
		if (scene->entities[entity_order[i]].enabled)
			continue ;
		render_sprite(&scene->entities[entity_order[i]], &scene->player, data,
			data->current_animation_frame
			% (scene->textures[KEY_TEX]->width
				/ scene->textures[KEY_TEX]->height));
	}
}
