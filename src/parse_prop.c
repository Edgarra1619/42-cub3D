/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:32:42 by vde-albu          #+#    #+#             */
/*   Updated: 2025/12/22 18:32:43 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d/cub3d.h>
#include <cub3d/parse.h>
#include <cub3d/strings.h>

#include <libft.h>

#include <mlx.h>

#include <limits.h>
#include <errno.h>

static int	parse_texture(const char *id, t_scene *scene, int fd, void *mlx);
static int	parse_color(const char *id, t_scene *scene, int fd);
static int	get_color(t_color *col, const char *str);
static int	parse_color_channel(unsigned char *channel, const char **str);

int	parse_prop(t_scene *const scene, const int fd, void *const mlx)
{
	char	id[PROP_SIZE];
	char	type;

	if (read_value(fd, id, PROP_SIZE))
		return (print_error(SECT_PARSE, ERR_INV_PROP));
	type = get_prop_type(id);
	if (type == TEXTURE)
		return (parse_texture(id, scene, fd, mlx));
	if (type == COLOR)
		return (parse_color(id, scene, fd));
	return (print_error(SECT_PARSE, ERR_INV_PROP));
}

static int	parse_texture(
	const char *const id, t_scene *const scene, const int fd, void *const mlx)
{
	const unsigned char	tex_id = get_texture_id(id);
	char				file[PATH_MAX];
	int					foo;

	if (scene->textures[tex_id])
		return (print_error(SECT_PARSE, ERR_DUP_PROP));
	if (read_line(fd, file, PATH_MAX))
		return (print_error(SECT_PARSE, ERR_PATH_MAX));
	scene->textures[tex_id] = mlx_xpm_file_to_image(mlx, file, &foo, &foo);
	if (!scene->textures[tex_id])
	{
		if (errno == 0)
			return (print_error(SECT_INIT, ERR_INV_TEX));
		return (print_error(SECT_INIT, NULL));
	}
	if (tex_id == KEY_TEX
		&& scene->textures[tex_id]->width % scene->textures[tex_id]->height)
		return (print_error(SECT_INIT, ERR_TEX_SIZE));
	return (0);
}

static int	parse_color(
	const char *const id, t_scene *const scene, const int fd)
{
	const unsigned char	col_id = get_color_id(id);
	char				buffer[COLOR_SIZE];

	if (scene->colors[col_id].a)
		return (print_error(SECT_PARSE, ERR_DUP_PROP));
	if (read_line(fd, buffer, COLOR_SIZE)
		|| get_color(scene->colors + col_id, buffer))
		return (print_error(SECT_PARSE, ERR_INV_COL));
	return (0);
}

static int	get_color(t_color *const col, const char *str)
{
	if (parse_color_channel(&col->r, &str)
		|| parse_color_channel(&col->g, &str)
		|| parse_color_channel(&col->b, &str)
		|| str[-1] == ',')
		return (1);
	col->a = 1;
	return (0);
}

static int	parse_color_channel(unsigned char *channel, const char **str)
{
	const int	num = ft_atoi(*str);
	int			i;

	if (num < 0 || num > UCHAR_MAX)
		return (1);
	i = 0;
	while (**str != '\0' && **str != ',')
	{
		if (i >= 3 || !ft_isdigit(**str))
			return (1);
		i++;
		(*str)++;
	}
	if (**str == ',')
		(*str)++;
	*channel = num;
	return (0);
}
