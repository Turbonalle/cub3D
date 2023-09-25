#include "../incl/cub3d.h"

int all_digits(char *str, int argument)
{
	int i;

	i = -1;
	while (str[++i])
	{
		// if (argument == 2 && str[i] == '\n')
		// 	break ;
		if (!ft_isdigit(str[i]))
			return (FAIL);
	}
	return (SUCCESS);
}

int get_color(cub3d_t *cub3d, int element, char **info)
{
	int i;
	int color_part;
	int color;
	char **rgb;

	rgb = ft_split(info[1], ',');
	free_info(info);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_info(rgb), err("Color: Wrong amount of arguments"));
	i = -1;
	while (++i < 3)
	{
		if (!all_digits(rgb[i], i))
			return (free_info(rgb), err("Color: Only digits allowed"));
		color_part = ft_atoi(rgb[i]);
		if (color_part < 0 || color_part > 255)
			return (free_info(rgb), err("Color: Invalid value"));
		color = (color << 8) + color_part;
	}
	if (element == F)
		cub3d->floor_color = color;
	else
		cub3d->ceiling_color = color;
	free_info(rgb);
	return (SUCCESS);
}
