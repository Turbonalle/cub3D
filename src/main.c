#include "../incl/cub3d.h"

int err(char *error_message)
{
	printf(TERMINAL_RED);
	printf("Error: %s\n", error_message);
	printf(TERMINAL_RESET);
	return (FAIL);
}

int main(int ac, char **av)
{
	cub3d_t	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	read_cub_file(&cub3d, av[1]);
	printf("NO = %s\n", cub3d.texture[NO].path);
	printf("SO = %s\n", cub3d.texture[SO].path);
	printf("WE = %s\n", cub3d.texture[WE].path);
	printf("EA = %s\n", cub3d.texture[EA].path);
	printf("floor_color = %d\n", cub3d.floor_color);
	printf("ceiling_color = %d\n", cub3d.ceiling_color);
	// if (read_map_file(&cub3d, av[1]) && init_data(&cub3d))
	// 	start_game(&cub3d);
	return (0);
}