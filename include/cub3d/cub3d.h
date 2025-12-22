/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:35:59 by vde-albu          #+#    #+#             */
/*   Updated: 2025/12/22 18:36:00 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <cub3d/types.h>

int		init(t_data *data, const char *file);
int		loop(t_data *data);
void	render_minimap(t_minimap *minimap, const t_scene *scene);
void	render_camera(t_scene *scene, t_data *data);
int		print_error(const char *type, const char *msg);

#endif
