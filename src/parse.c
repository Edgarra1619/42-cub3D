#include <cub3d/defines.h>
#include <cub3d/parse.h>

#include <libft.h>

char	get_prop_type(const char *const id)
{
	if (!ft_strcmp(id, "NO") || !ft_strcmp(id, "EA") || !ft_strcmp(id, "SO")
		|| !ft_strcmp(id, "WE") || !ft_strcmp(id, "K") || !ft_strcmp(id, "D"))
		return (TEXTURE);
	if (!ft_strcmp(id, "F") || !ft_strcmp(id, "C"))
		return (COLOR);
	return (-1);
}

char	get_texture_id(const char *const id)
{
	if (!ft_strcmp(id, "NO"))
		return (NORTH_WALL_TEX);
	if (!ft_strcmp(id, "EA"))
		return (EAST_WALL_TEX);
	if (!ft_strcmp(id, "SO"))
		return (SOUTH_WALL_TEX);
	if (!ft_strcmp(id, "WE"))
		return (WEST_WALL_TEX);
	if (!ft_strcmp(id, "K"))
		return (KEY_TEX);
	if (!ft_strcmp(id, "D"))
		return (DOOR_TEX);
	return (-1);
}

char	get_color_id(const char *const id)
{
	if (!ft_strcmp(id, "F"))
		return (FLOOR_COL);
	if (!ft_strcmp(id, "C"))
		return (CEILING_COL);
	return (-1);
}
char	get_cell_type(const char cell)
{
	if (cell == '0')
		return (SPACE);
	if (cell == '1' || cell == ' ')
		return (WALL);
	if (cell == 'K' || cell == '|' || cell == '-')
		return (ENTITY);
	if (cell == 'N' || cell == 'E' || cell == 'S' || cell == 'W')
		return (PLAYER);
	return (-1);
}

char	get_entity_type(const char cell)
{
	if (cell == 'K')
		return (KEY);
	if (cell == '|' || cell == '-')
		return (DOOR);
	return (-1);
}
