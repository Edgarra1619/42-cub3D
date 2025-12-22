/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:31:29 by vde-albu          #+#    #+#             */
/*   Updated: 2025/12/22 18:31:33 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d/cub3d.h>
#include <cub3d/strings.h>

#include <libft.h>

#include <mlx.h>

#include <unistd.h>

static void	clean_mlx(t_data *data);

int	main(int argc, char **argv)
{
	static t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd(MSG_USAGE, 1);
		return (1);
	}
	if (init(&data, argv[1]))
	{
		clean_mlx(&data);
		return (1);
	}
	mlx_loop(data.display);
	clean_mlx(&data);
}

static void	clean_mlx(t_data *const data)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		if (data->scene.textures[i])
			mlx_destroy_image(data->display, data->scene.textures[i]);
		i++;
	}
	if (data->buffer)
		mlx_destroy_image(data->display, data->buffer);
	if (data->window)
		mlx_destroy_window(data->display, data->window);
	mlx_destroy_display(data->display);
	free(data->display);
}
