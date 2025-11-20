#include <cub3d/vector.h>

#include <math.h>

t_vec2	sum_vec2(const t_vec2 a, const t_vec2 b)
{
	return ((t_vec2){a.x + b.x, a.y + b.y});
}

t_vec2	mult_vec2i(const t_vec2 a, const int b)
{
	return ((t_vec2){a.x * b, a.y * b});
}

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
	const float	mag = sqrt(pow(vec.x, 2) + pow(vec.y, 2));

	return ((t_vec2f){vec.x / mag, vec.y / mag});
}
