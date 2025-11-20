#ifndef CUB3D_H
# define CUB3D_H

# include <cub3d/types.h>
# include <cub3d/vector.h>

# include <mlx_int.h>

int		init_scene(t_scene *scene, const char *file, void *mlx);
int		print_error(const char *type, const char *msg);
void	render_minimap(t_minimap *minimap, t_scene *scene);
int		loop(t_data *data);
#endif
