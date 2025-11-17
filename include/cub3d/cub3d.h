#ifndef CUB3D_H
# define CUB3D_H

# include <cub3d/types.h>
# include <cub3d/vector.h>
# include <mlx_int.h>


void	render_minimap(t_img *buffer, t_scene *scene);
int		print_error(const char *type, const char *msg);
int		loop(t_data *data);
int		init_scene(t_scene *const scene, const char *const file);


#endif
