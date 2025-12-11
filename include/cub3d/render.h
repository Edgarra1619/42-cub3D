#ifndef RENDER_H
# define RENDER_H

# include <cub3d/types.h>
# include <cub3d/raycast.h>

# ifndef MINIMAP_SIZE
#  define MINIMAP_SIZE 10
# endif

void		draw_square(t_img *buffer, t_vec2 ul, t_vec2 dr, t_color color);
t_rayhit	cast_render_ray(t_scene *const scene, const t_vec2f pos, const t_vec2f dir);

#endif
