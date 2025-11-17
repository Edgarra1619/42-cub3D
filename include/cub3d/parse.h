#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>
# include <cub3d/types.h>

char	read_char(int fd, bool peek);
int		parse_map(t_scene *scene, int fd);

#endif
