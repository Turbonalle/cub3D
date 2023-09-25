#include "../incl/cub3d.h"

void free_info(char **info)
{
	int i;

	i = -1;
	while (info[++i])
		free(info[i]);
	free(info);
}

int elements_found(int *element_found)
{
	int i;

	i = -1;
	while (++i < 6)
	{
		if (!element_found[i])
			return (FAIL);
	}
	return (SUCCESS);
}

int get_element(cub3d_t *cub3d, int element, char **info)
{
	if (cub3d->element_found[element])
		return (free_info(info), err("Duplicate element found"));
	cub3d->element_found[element] = 1;
	if (element == F || element == C)
		return (get_color(cub3d, element, info));
	else
		return (get_texture(cub3d, element, info));
}

int find_element(cub3d_t *cub3d, char *line)
{
	char **info;

	info = ft_split(line, ' ');
	if (!info || !info[0] || !info[1])
		return (FAIL);
	if (ft_strcmp(info[0], "NO") == 0)
		return (get_element(cub3d, NO, info));
	else if (ft_strcmp(info[0], "SO") == 0)
		return (get_element(cub3d, SO, info));
	else if (ft_strcmp(info[0], "WE") == 0)
		return (get_element(cub3d, WE, info));
	else if (ft_strcmp(info[0], "EA") == 0)
		return (get_element(cub3d, EA, info));
	else if (ft_strcmp(info[0], "F") == 0)
		return (get_element(cub3d, F, info));
	else if (ft_strcmp(info[0], "C") == 0)
		return (get_element(cub3d, C, info));
}

int get_elements(cub3d_t *cub3d, int fd)
{
	char *line;
	int i;

	i = 0;
	while (i < 6)
		cub3d->element_found[i++] = 0;
	while (!elements_found(cub3d->element_found))
	{
		line = get_next_line(fd);
		if (!line)
			return (err("Failed to read map file"));
		if (line[0] == '\n')
			continue ;
		if (!find_element(cub3d, line))
		{
			free(line);	
			return (FAIL);
		}
		free(line);
	}
	return (SUCCESS);
}