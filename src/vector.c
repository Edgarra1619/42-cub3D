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
