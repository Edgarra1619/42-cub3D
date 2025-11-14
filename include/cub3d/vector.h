#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec2f
{
	float	x;
	float	y;
}	t_vec2f;

t_vec2f	sum_vec2f(const t_vec2f a, const t_vec2f b);
t_vec2f	norm_vec2f(const t_vec2f vec);

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

t_vec2	sum_vec2(const t_vec2 a, const t_vec2 b);
t_vec2	mult_vec2i(const t_vec2 a, const int b);
t_vec2	norm_vec2(const t_vec2 vec);

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

#endif
