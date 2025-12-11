#ifndef HOOKS_H
# define HOOKS_H

# include <cub3d/types.h>
# include <cub3d/vector.h>

int	keyboard_up_hook(int keycode, t_data *data);
int	keyboard_down_hook(int keycode, t_data *data);

#endif
