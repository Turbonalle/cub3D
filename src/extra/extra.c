/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:40 by slampine          #+#    #+#             */
/*   Updated: 2023/11/23 10:20:15 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void print_info(cub3d_t *cub3d)
{
	printf(TERMINAL_CYAN"INFO:\n"TERMINAL_RESET);
	printf(TERMINAL_GREEN"NO"TERMINAL_RESET" = %s\n", cub3d->texture[NO].path);
	printf(TERMINAL_GREEN"SO"TERMINAL_RESET" = %s\n", cub3d->texture[SO].path);
	printf(TERMINAL_GREEN"WE"TERMINAL_RESET" = %s\n", cub3d->texture[WE].path);
	printf(TERMINAL_GREEN"EA"TERMINAL_RESET" = %s\n", cub3d->texture[EA].path);
	printf(TERMINAL_GREEN"floor_color"TERMINAL_RESET" = %d\n", cub3d->floor_color);
	printf(TERMINAL_GREEN"ceiling_color"TERMINAL_RESET" = %d\n", cub3d->ceiling_color);
	printf(TERMINAL_GREEN"starting_pos"TERMINAL_RESET" = %d, %d\n", cub3d->starting_pos.x, cub3d->starting_pos.y);
	printf(TERMINAL_GREEN"starting_dir"TERMINAL_RESET" = %c\n", cub3d->starting_dir);
	int i = -1;
	while (cub3d->map[++i])
		printf("map[%02d] = %s\n", i, cub3d->map[i]);
}

//------------------------------------------------------------------------------

void print_array(char **array, char *name)
{
	printf(TERMINAL_CYAN"%s:\n"TERMINAL_RESET, name);
	int i = -1;
	while (array[++i])
		printf("array[%d] = %s", i, array[i]);
}

//------------------------------------------------------------------------------

void print_map(char **map)
{
	int i = -1;
	while (map[++i])
		printf("map[%02d] = |%s|\n", i, map[i]);
}

//------------------------------------------------------------------------------

void test(void)
{
	int fd = open("Maps/test.txt", O_RDONLY);
	char *line = get_next_line(fd);
	int i = 0;
	while (line)
	{
		printf("line[%d] = %s", i++, line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
}
