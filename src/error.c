/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:32:04 by vde-albu          #+#    #+#             */
/*   Updated: 2025/12/22 18:32:05 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d/cub3d.h>
#include <cub3d/strings.h>

#include <libft.h>

#include <errno.h>

static void	buffer_error(const char *str);

int	print_error(const char *const type, const char *const msg)
{
	buffer_error(PROG_NAME);
	buffer_error(": ");
	buffer_error(type);
	buffer_error(" error: ");
	if (msg)
		buffer_error(msg);
	else
		buffer_error(strerror(errno));
	buffer_error(NULL);
	return (1);
}

static void	buffer_error(const char *const str)
{
	static char	buffer[ERROR_MAX];

	if (str)
		ft_strlcat(buffer, str, ERROR_MAX);
	else
	{
		ft_strlcat(buffer, "\n", ERROR_MAX);
		write(2, buffer, ft_strlen(buffer));
		buffer[0] = '\0';
	}
}
