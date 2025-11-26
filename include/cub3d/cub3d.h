#ifndef CUB3D_H
# define CUB3D_H

# include <cub3d/types.h>

int		init(t_data *data, const char *file);
int		loop(t_data *data);
void	render_minimap(t_minimap *minimap, const t_scene *scene);
int		print_error(const char *type, const char *msg);

#endif
