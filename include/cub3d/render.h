#ifndef RENDER_H
# define RENDER_H

# include <cub3d/types.h>
# include <cub3d/raycast.h>

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1280
# endif
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 720
# endif
# ifndef MINIMAP_WIDTH
#  define MINIMAP_WIDTH 242
# endif
# ifndef MINIMAP_SIZE
#  define MINIMAP_SIZE 10
# endif

void		draw_square(t_img *buffer, t_vec2 ul, t_vec2 dr, t_color color);
t_vec2f		world_to_camera(const t_player *const player, const t_vec2f pos);
t_rayhit	cast_render_ray(t_scene *const scene,
				const t_vec2f pos, const t_vec2f dir);
void		render_sprites(t_scene *scene, t_data *data);

#endif
