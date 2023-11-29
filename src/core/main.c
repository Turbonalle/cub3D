
#include "../incl/cub3d.h"

int	check_ext(char *str)
{
	int		len;
	int		i;
	char	*ext;

	i = 0;
	len = ft_strlen(str) - 1;
	ext = "buc.";
	while (ext[i])
	{
		if (str[len] != ext[i])
			return (0);
		len--;
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	cub3d_t	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	printf("1\n");
	if (!check_ext(av[1]))
		return (err("Invalid extension"));
	printf("2\n");
	if (!read_cub_file(&cub3d, av[1]) || !init_cub3d(&cub3d))
		return (1);
	printf("3\n");
	if (!init_enemy(&cub3d))
		return (1);
	printf("4\n");
	if (init_doors_and_keys(&cub3d) == FAIL)
		return (1);
	printf("5\n");
	// TODO DOORS: validity check
	print_info(&cub3d); // DEBUG
	start_game(&cub3d);
	free_cub3d(&cub3d);
	return (0);
}
