/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:35:27 by edgribei          #+#    #+#             */
/*   Updated: 2025/12/22 18:38:20 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <cub3d/types.h>
# include <cub3d/vector.h>

int	keyboard_up_hook(int keycode, t_data *data);
int	keyboard_down_hook(int keycode, t_data *data);

#endif
