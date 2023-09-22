#include "../incl/cub3d.h"

int err(char *error_message)
{
	printf(RED"Error: %s\n"RESET, error_message);
	return (FAIL);
}

int main(int ac, char **av)
{
	cub3d_t	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	if (read_map_file(&cub3d, av[1]) && init_data(&cub3d))
		start_game(&cub3d);
	return (0);
}