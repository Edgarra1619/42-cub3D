#ifndef HOOKS_H

# include <cub3d/types.h>
# include <cub3d/vector.h>

int	keyboard_up_hook(int keycode, t_data *data);
int	keyboard_down_hook(int keycode, t_data *data);
int	mouse_up_hook(int button, t_vec3 pos, t_data *data);
int	mouse_down_hook(int button, t_vec3 pos, t_data *data);
int	mouse_move_hook(t_vec2 pos, t_data *data);

#endif
