#include "../incl/cub3d.h"

int err(char *error_message)
{
	printf(TERMINAL_RED);
	printf("Error: %s\n", error_message);
	printf(TERMINAL_RESET);
	return (FAIL);
}

void free_info(char **info)
{
	int i;

	i = -1;
	while (info[++i])
		free(info[i]);
	free(info);
}

void free_cub3d(cub3d_t *cub3d)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (cub3d->texture[i].path)
			free(cub3d->texture[i].path);
		// if (cub3d->texture[i].img)
		// 	free(cub3d->texture[i].img);
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

	print_info(&cub3d); // DEBUG
	free_cub3d(&cub3d);
	return (0);
}