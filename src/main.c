#include "../incl/cub3d.h"

int err(char *error_message)
{
	printf(RED"Error: %s\n"RESET, error_message);
	return (FAIL);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	get_map(av[1]);
	return (0);
}