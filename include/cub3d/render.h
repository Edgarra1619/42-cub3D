#ifndef RENDER_H
# define RENDER_H

# include <cub3d/types.h>

# ifndef MINIMAP_SIZE
#  define MINIMAP_SIZE 10
# endif

void	draw_square(t_img *buffer, t_vec2 ul, t_vec2 dr, t_color color);

#endif
