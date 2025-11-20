#ifndef PARSE_H
# define PARSE_H

# include <cub3d/types.h>

# include <stdbool.h>

# define PROP_SIZE	3
# define COLOR_SIZE	12

enum e_prop
{
	TEXTURE,
	COLOR,
};

int		parse_prop(t_scene *scene, int fd, void *mlx);
int		parse_map(t_scene *scene, int fd);
int		validate_map(const t_scene *scene);
char	get_prop_type(const char *id);
char	get_texture_id(const char *id);
char	get_color_id(const char *id);
char	get_cell_type(char cell);
char	get_entity_type(char cell);
char	read_char(int fd, bool peek);
int		read_value(int fd, char *dest, int size);
int		read_line(int fd, char *dest, int size);

#endif
