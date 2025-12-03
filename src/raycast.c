#include <cub3d/defines.h>
#include <cub3d/vector.h>
#include <cub3d/raycast.h>
#include <cub3d/types.h>

#include <math.h>

static void	fill_rayhelper(struct s_rayhelper *helper, t_vec2f pos, t_vec2f dir);

//TODO: make a limited distance version
//TODO: make one for sprite rendering (needs to return multiple results)

//the value returned in hit_positon is the horizontal position inside the wall
t_rayhit	cast_render_ray(t_scene *const scene, const t_vec2f pos, const t_vec2f dir)
{
	t_rayhit			hit;
	struct s_rayhelper	info;

	fill_rayhelper(&info, pos, dir);
	hit.hit = 0;
	while (!hit.hit)
	{
		if (info.length.x < info.length.y)
		{
			info.length.x += info.length_step.x;
			info.map_pos.x += info.map_step.x;
			if (info.map_step.x < 0)
				hit.side_hit = EAST;
			else
				hit.side_hit = WEST;
		}
		else
		{
			info.length.y += info.length_step.y;
			info.map_pos.y += info.map_step.y;
			if (info.map_step.y < 0)
				hit.side_hit = NORTH;
			else
				hit.side_hit = SOUTH;
		}
		if (scene->map[info.map_pos.x][info.map_pos.y] == WALL)
			hit.hit = 1;
	}
	if (hit.side_hit & 0b10)
	{
		hit.projDist = info.length.x - info.length_step.x;
		hit.hit_position.x = floorf(pos.x + hit.projDist * dir.x);
	}
	else
	{
		hit.projDist = info.length.y - info.length_step.y;
		hit.hit_position.x = floorf(pos.y + hit.projDist * dir.y);
	}
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
