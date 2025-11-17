#include <libft.h>
#include <cub3d/defines.h>

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
