#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>
# include <cub3d/types.h>

char	read_char(int fd, bool peek);
int		parse_map(t_scene *scene, int fd);
int		validate_map(const t_scene *scene);
char	get_cell_type(char cell);
char	get_entity_type(char cell);

#endif
