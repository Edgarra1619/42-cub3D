#include "libft.h"
#include <cub3d/vector.h>
#include <cub3d/types.h>
#include <mlx_int.h>

void	draw_square(t_img *buffer, t_vec2 ul, t_vec2 dr, t_color color)
{
	char *const	data = buffer->data;
	const int	width = buffer->width;
	int	tmp;

	ul.x = ft_max(ul.x, 0);
	ul.y = ft_max(ul.y, 0);
	dr.x = ft_min(dr.x, buffer->width);
	dr.y = ft_min(dr.y, buffer->height);

	tmp = ul.x;
	while (ul.y < dr.y)
	{
		ul.x = tmp;
		while (ul.x < dr.x)
		{
			((int*) data)[ul.x + ul.y * width] = color.color;
			ul.x++;
		}
		ul.y++;
	}


}
