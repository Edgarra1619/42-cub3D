/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:36:09 by vde-albu          #+#    #+#             */
/*   Updated: 2025/12/22 18:37:20 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1280
# endif
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 720
# endif
# ifndef READ_SIZE
#  define READ_SIZE 1024
# endif
# ifndef ERROR_MAX
#  define ERROR_MAX 1024
# endif
# ifndef MAP_MAX
#  define MAP_MAX 1024
# endif
# ifndef ENTITY_MAX
#  define ENTITY_MAX 64
# endif

enum	e_std_colors
{
	RED = 0xFFFF0000,
	GREEN = 0xFF00FF00,
	BLUE = 0xFF0000FF,
	YELLOW = 0xFFFFFF00,
	WHITE = 0xFFFFFFFF,
	GRAY = 0xFF444444,
	BLACK = 0xFF000000,
};

enum	e_input
{
	KEYCODEW = 1 << 0,
	KEYCODES = 1 << 1,
	KEYCODEA = 1 << 2,
	KEYCODED = 1 << 3,
	KEYCODEQ = 1 << 4,
	KEYCODEE = 1 << 5,
	KEYCODELEFT = 1 << 6,
	KEYCODERIGHT = 1 << 7,
	BUTTONL = 1 << 8,
	BUTTONR = 1 << 9,
};

enum e_cell
{
	SPACE,
	WALL,
	ENTITY,
	PLAYER,
};

enum e_entity
{
	KEY,
	DOOR,
};

enum e_texture
{
	NORTH_WALL_TEX,
	EAST_WALL_TEX,
	SOUTH_WALL_TEX,
	WEST_WALL_TEX,
	KEY_TEX,
	DOOR_TEX,
	TEXTURE_COUNT,
};

enum e_color
{
	FLOOR_COL,
	CEILING_COL,
	COLOR_COUNT,
};

#endif
