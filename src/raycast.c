#include <cub3d/defines.h>
#include <cub3d/vector.h>
#include <cub3d/raycast.h>
#include <cub3d/types.h>

#include <math.h>

static void	render_ray_step(struct s_rayhelper *info, t_rayhit *hit);
static int	render_ray_check(t_scene *scene, struct s_rayhelper *info, t_rayhit *hit);
static void	fill_rayhelper
		(struct s_rayhelper *helper, t_vec2f pos, t_vec2f dir);

//TODO: make a limited distance version
//TODO: make one for sprite rendering (needs to return multiple results)

//the value returned in hit_positon is the horizontal position inside the wall
t_rayhit	cast_render_ray
		(t_scene *const scene, const t_vec2f pos, const t_vec2f dir)
{
	t_rayhit			hit;
	struct s_rayhelper	info;

	fill_rayhelper(&info, pos, dir);
	while (!render_ray_check(scene, &info, &hit))
		render_ray_step(&info, &hit);
	if (hit.side_hit & 0b01)
	{
		hit.projDist = info.length.x - info.length_step.x;
		hit.hit_position.x = pos.y + hit.projDist * dir.y;
	}
	else
	{
		hit.projDist = info.length.y - info.length_step.y;
		hit.hit_position.x = pos.x + hit.projDist * dir.x;
	}
	hit.hit_position.x = hit.hit_position.x - floorf(hit.hit_position.x);
	if (hit.side_hit >> 2)
		hit.side_hit = DOOR_TEX;
	return (hit);
}

static void	fill_rayhelper(struct s_rayhelper *const helper,
						const t_vec2f pos, const t_vec2f dir)
{
	helper->map_pos = (t_vec2) {(int) pos.x, (int) pos.y};
	helper->length_step = (t_vec2f) {fabsf(1 / dir.x), fabsf(1 / dir.y)};
	if (dir.x < 0)
	{
		helper->map_step.x = -1;
		helper->length.x = (pos.x - helper->map_pos.x) * helper->length_step.x;
	}
	else
	{
		helper->map_step.x = 1;
		helper->length.x = (helper->map_pos.x + 1 - pos.x) * helper->length_step.x;
	}
	if (dir.y < 0)
	{
		helper->map_step.y = -1;
		helper->length.y = (pos.y - helper->map_pos.y) * helper->length_step.y;
	}
	else
	{
		helper->map_step.y = 1;
		helper->length.y = (helper->map_pos.y + 1 - pos.y) * helper->length_step.y;
	}
}

static void	render_ray_step(struct s_rayhelper *info, t_rayhit *hit)
{
	if (info->length.x < info->length.y)
	{
		info->length.x += info->length_step.x;
		info->map_pos.x += info->map_step.x;
		if (info->map_step.x < 0)
			hit->side_hit = EAST;
		else
			hit->side_hit = WEST;
	}
	else
	{
		info->length.y += info->length_step.y;
		info->map_pos.y += info->map_step.y;
		if (info->map_step.y < 0)
			hit->side_hit = SOUTH;
		else
			hit->side_hit = NORTH;
	}
}

static int	render_ray_check(t_scene *scene, struct s_rayhelper *info, t_rayhit *hit)
{
	t_entity	*entity;

	if (scene->map[info->map_pos.x][info->map_pos.y] == 0)
		return (0);
	if (scene->map[info->map_pos.x][info->map_pos.y] == WALL)
		return (1);
	entity = scene->entities + (scene->map[info->map_pos.x][info->map_pos.y] >> 2);
	if (entity->type == DOOR && !entity->open)
	{
		if (!(hit->side_hit & 0b01) && !(info->length.y - info->length_step.y + info->length_step.y/4 < info->length.x))
			return (0);
		if (hit->side_hit & 0b01 && !(info->length.x - info->length_step.x + info->length_step.x/4 < info->length.y))
			return (0);
		hit->side_hit |= 0b100;
		info->length.x += info->length_step.x / 4;
		info->length.y += info->length_step.y / 4;
		return (1);
	}
	return (0);
}
