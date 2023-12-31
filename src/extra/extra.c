
#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void print_level_info(level_t *level)
{
	printf(TERMINAL_CYAN"INFO:\n"TERMINAL_RESET);
	printf(TERMINAL_GREEN"NO"TERMINAL_RESET" = %s\n", level->texture[NO].path);
	printf(TERMINAL_GREEN"SO"TERMINAL_RESET" = %s\n", level->texture[SO].path);
	printf(TERMINAL_GREEN"WE"TERMINAL_RESET" = %s\n", level->texture[WE].path);
	printf(TERMINAL_GREEN"EA"TERMINAL_RESET" = %s\n", level->texture[EA].path);
	printf(TERMINAL_GREEN"floor_color"TERMINAL_RESET" = %d\n", level->floor_color);
	printf(TERMINAL_GREEN"ceiling_color"TERMINAL_RESET" = %d\n", level->ceiling_color);
	printf(TERMINAL_GREEN"starting_pos"TERMINAL_RESET" = %d, %d\n", level->starting_pos.x, level->starting_pos.y);
	printf(TERMINAL_GREEN"starting_dir"TERMINAL_RESET" = %c\n", level->starting_dir);
	int i = -1;
	while (level->map[++i])
		printf("map[%02d] = %s\n", i, level->map[i]);
}

//------------------------------------------------------------------------------

void print_array(char **array, char *name)
{
	printf(TERMINAL_CYAN"%s:\n"TERMINAL_RESET, name);
	int i = -1;
	while (array[++i])
		printf("array[%d] = %s\n", i, array[i]);
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

void print_settings(cub3d_t *cub3d)
{
	printf(TERMINAL_CYAN"[SETTINGS]\n"TERMINAL_RESET);
	printf("FPS: "TERMINAL_GREEN"%d"TERMINAL_RESET"\n", cub3d->settings.fps);
	printf("Fisheye: "TERMINAL_GREEN"%d"TERMINAL_RESET"\n", cub3d->settings.fisheye);
	printf("Mouse: "TERMINAL_GREEN"%d"TERMINAL_RESET"\n", cub3d->settings.mouse);
}


void	print_letter_indexes(name_menu_t *menu, int backspace)
{
	int i;

	i = -1;
	while (++i < menu->current)
	{
		if (i == menu->current - 1 && backspace == 0)
			printf(TERMINAL_GREEN);
		else if (i == menu->current - 1 && backspace == 1)
			printf(TERMINAL_RED);
		else
			printf(TERMINAL_RESET);
		if (menu->name[i] == '\0')
			printf("   ");
		else
			printf(" %c ", menu->name[i]);
	}
	printf(TERMINAL_RESET);
	printf("\n");
	i = -1;
	while (++i < menu->current)
	{
		if (i == menu->current - 1 && backspace == 0)
			printf(TERMINAL_GREEN);
		else if (i == menu->current - 1 && backspace == 1)
			printf(TERMINAL_RED);
		else
			printf(TERMINAL_RESET);
		if (menu->letter_index[i] == 0)
			printf("   ");
		else
		{
			if (menu->letter_index[i] < 10)
				printf(" %d ", menu->letter_index[i]);
			else
				printf("%d ", menu->letter_index[i]);
		}
	}
	printf(TERMINAL_RESET);
	printf("\n\n");
}