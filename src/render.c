#include "libft.h"
#include <cub3d/raycast.h>
#include <cub3d/vector.h>
#include <cub3d/types.h>
#include <cub3d/render.h>

#include <math.h>

static void	clear_screen(t_scene *scene, t_img *buffer)
{
	const t_vec2	buff_size = (t_vec2) {buffer->width, buffer->height};
	float			dist_mult;
	t_color		color;
	t_vec2	i;

	i.y = 0;
	while (i.y < buff_size.y / 2)
	{
		color = scene->colors[0];
		dist_mult = 1.0 / (3 + ft_clampf(5 * ((float) (buffer->height / 2.0)
								/ (buffer->height / 2.0 - i.y) - 1), 1, 255));
		color.r = color.r * dist_mult;
		color.g = color.g * dist_mult;
		color.b = color.b * dist_mult;
		color.a = color.a * dist_mult;
		i.x = 0;
		while (i.x < buff_size.x)
			((int*)buffer->data)[i.x++ + i.y * buff_size.x] = color.color;
		i.y++;
	}
	i.y = buff_size.y;
	while (i.y > buff_size.y / 2)
	{
		color = scene->colors[1];
		dist_mult = 1 / (3 + ft_clampf(5 * ((float) (buffer->height / 2.0)
								/ (i.y - buffer->height / 2.0) - 1), 1, 255));
		color.r = color.r * dist_mult;
		color.g = color.g * dist_mult;
		color.b = color.b * dist_mult;
		color.a = color.a * dist_mult;
		i.x = 0;
		while (i.x < buff_size.x)
			((int*)buffer->data)[i.x++ + i.y * buff_size.x] = color.color;
		i.y--;
	}
}

static void	render_column_loop(t_scene *scene, t_img *buffer, int col, t_rayhit hit)
{
	const float	dist_mult = 1 / (3 + ft_clampf(5 * (hit.projDist - 1), 1, 255));
	const int	height = buffer->height / hit.projDist;
	const int	start = buffer->height / 2 - height / 2;
	t_color		pixel;
	t_vec2		iter;

	if (hit.side_hit == SOUTH || hit.side_hit == EAST)
		hit.hit_position.x = 1 - hit.hit_position.x;
	iter.x = ft_max(0, start);
	iter.y = ft_min(start + height, buffer->height);
	while (iter.x < iter.y)
	{
		pixel = ((t_color*)(scene->textures[hit.side_hit]->data +
			(int) (scene->textures[hit.side_hit]->size_line *
			(int) ((float) (iter.x - start) / height
			* scene->textures[hit.side_hit]->height))))
			[(int)(scene->textures[hit.side_hit]->width * hit.hit_position.x)];
		pixel.r = pixel.r * dist_mult;
		pixel.g = pixel.g * dist_mult;
		pixel.b = pixel.b * dist_mult;
		pixel.a = pixel.a * dist_mult;
		((int*)(buffer->data + buffer->size_line * iter.x))[col] = pixel.color;
		iter.x++;
	}
}

//height = buffer->height / dist
//start = buffer->height / 2 - height / 2
//end = min(start + height, buffer->height) - i;
//i = max(0, start)
//i < height && i + start < buffer->height
//place at start + i with texture coord i/height using uv coords
static void	render_column(t_scene *scene, t_img *buffer, t_vec2f dir, int col)
{
	const t_rayhit			hit = cast_render_ray(scene, scene->player.pos, dir);

	render_column_loop(scene, buffer, col, hit);
}

void	render_camera(t_scene *scene, t_img *buffer)
{
	const int		width = buffer->width;
	const t_vec2f	step =
		mult_vec2ff(rot_vec2ff(scene->player.dir, M_PI_2), (float) 1 / (width));
	t_vec2f			dir;
	int				i;

	clear_screen(scene, buffer);
	dir = sum_vec2f(scene->player.dir, mult_vec2ff(step, (float) - width / 2));
	i = 0;
	while (i < width)
	{
		render_column(scene, buffer, dir, i);
		dir = sum_vec2f(dir, step);
		i++;
	}
}
