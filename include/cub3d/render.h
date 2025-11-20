#ifndef RENDER_H
# define RENDER_H

# include <cub3d/vector.h>
# include <cub3d/types.h>

# include <mlx_int.h>

# ifndef MINIMAP_SIZE
#  define MINIMAP_SIZE 10
# endif

void	draw_square(t_img *buffer, t_vec2 UL, t_vec2 DR, t_color color);

#endif
