#include "../incl/cub3d.h"

int err(char *error_message)
{
	printf(TERMINAL_RED);
	printf("Error: %s\n", error_message);
	printf(TERMINAL_RESET);
	return (FAIL);
}

void free_cub3d(cub3d_t *cub3d)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (cub3d->texture[i].path)
			free(cub3d->texture[i].path);
		if (cub3d->texture[i].img)
			free(cub3d->texture[i].img);
	}
	i = -1;
	while (cub3d->map[++i])
		free(cub3d->map[i]);
	free(cub3d->map);
}

int main(int ac, char **av)
{
	cub3d_t	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	read_cub_file(&cub3d, av[1]);
	printf(TERMINAL_CYAN"INFO:\n"TERMINAL_RESET);
	printf(TERMINAL_GREEN"NO"TERMINAL_RESET" = %s\n", cub3d.texture[NO].path);
	printf(TERMINAL_GREEN"SO"TERMINAL_RESET" = %s\n", cub3d.texture[SO].path);
	printf(TERMINAL_GREEN"WE"TERMINAL_RESET" = %s\n", cub3d.texture[WE].path);
	printf(TERMINAL_GREEN"EA"TERMINAL_RESET" = %s\n", cub3d.texture[EA].path);
	printf(TERMINAL_GREEN"floor_color"TERMINAL_RESET" = %d\n", cub3d.floor_color);
	printf(TERMINAL_GREEN"ceiling_color"TERMINAL_RESET" = %d\n", cub3d.ceiling_color);
	printf(TERMINAL_GREEN"starting_pos"TERMINAL_RESET" = %d, %d\n", cub3d.starting_pos.x, cub3d.starting_pos.y);
	printf(TERMINAL_GREEN"starting_dir"TERMINAL_RESET" = %c\n", cub3d.starting_dir);
	int i = -1;
	while (cub3d.map[++i])
		printf("map[%d] = %s\n", i, cub3d.map[i]);
	free_cub3d(&cub3d);
	return (0);
}