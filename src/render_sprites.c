#include <cub3d/vector.h>
#include <cub3d/defines.h>
#include <cub3d/types.h>

#include <libft.h>

#include <stdbool.h>

static void	sort_sprites(int *order, float *distance, int count)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i;
		while (j < count - 1)
		{
			if (distance[order[j]] > distance[order[j + 1]])
			{
				tmp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	render_column_loop(t_data *data, int tex_col, int buffer_col, float dist)
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
		pixel = ((t_color*)(data->scene.textures[KEY_TEX]->data +
			(int) (data->scene.textures[KEY_TEX]->size_line *
			(int) ((float) (iter.x - start) / height
			* data->scene.textures[KEY_TEX]->height))))
			[(int)(tex_col)];
		if (pixel.a != 0)
			continue ;
		pixel.r = pixel.r * dist_mult;
		pixel.g = pixel.g * dist_mult;
		pixel.b = pixel.b * dist_mult;
		pixel.a = pixel.a * dist_mult;
		((int*)(data->buffer->data + data->buffer->size_line * iter.x))[buffer_col] = pixel.color;
	}
}

static void	fill_sprite_distance(t_scene *scene, int *order, float *distance, int count)
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

static void	fill_sprite_entities(t_scene *scene, int *order, int *count)
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

static t_vec2f	world_to_camera(t_player *player, t_vec2f pos)
{
	const t_vec2f	sprite_pos = (t_vec2f)
		{
			pos.x - player->pos.x + 0.5,
			pos.y - player->pos.y + 0.5
		};
	const float		matrix_helper = 1.0
		/ (player->cam_plane.x * player->dir.y - player->cam_plane.y * player->dir.x);

	return (t_vec2f)
		{
			matrix_helper *
				(player->dir.y * sprite_pos.x - player->dir.x * sprite_pos.y),
			matrix_helper *
				(player->cam_plane.x * sprite_pos.y - player->cam_plane.y * sprite_pos.x)
		};
}

static void	render_sprite(t_entity *entity, t_player *player, t_data *data)
{
	const t_vec2f	proj =
		world_to_camera(player, (t_vec2f){entity->pos.x, entity->pos.y });
	const int		pos = (float) (data->buffer->width / 2.0) * (1 + proj.x / proj.y * WINDOW_WIDTH / WINDOW_HEIGHT);
	const int		size = data->buffer->height / proj.y;
	const int		start = pos - size / 2;
	int				i;

	//if ( proj.y < 0)
	//	return ;
	i = ft_min(size, data->buffer->width - start);
	while (i > 0 && i > -start)
	{
		if (proj.y < data->zbuffer[start + i])
			render_column_loop(data,
					data->scene.textures[KEY_TEX]->height * ((data->current_animation_frame % 8) + ((float) i / size)), start + i, proj.y);
		i--;
	}
	//((int*)data->buffer->data)[pos] = RED;
}

void	render_sprites(t_scene *scene, t_data *data)
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
			continue;
		render_sprite(&scene->entities[entity_order[i]], &scene->player, data);
	}
}
