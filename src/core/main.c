#include "../incl/cub3d.h"

int	malloc_levels(cub3d_t *cub3d)
{
	int	i;

	cub3d->levels = malloc(sizeof(level_t) * (LEVELS + 1));
	if (!cub3d->levels)
		return (err("Failed to malloc levels"));
	i = -1;
	while (++i < LEVELS + 1)
		nullify_level(&cub3d->levels[i]);
	return (SUCCESS);
}

int	init_game(cub3d_t *cub3d, char *path)
{
	nullify_everything(cub3d);
	if (!check_ext(path))
		return (err("Invalid extension"));
	if (!malloc_levels(cub3d))
		return (FAIL);
	cub3d->level = &cub3d->levels[0];
	if (!read_cub_file(cub3d->level, path))
		return (FAIL);
	printf("READ MAIN CUB FILE\n");
	if (!read_all_levels(cub3d))
		return (FAIL);
	printf("init_cub3d\n");
	if (!init_cub3d(cub3d))
		return (FAIL);
	printf("init_records\n");
	if (!read_records(cub3d))
		return (err("Failed to read records"));
	if (!init_leaderboard(cub3d, &cub3d->leaderboard))
		return (FAIL);
	if (!init_enemy_frames(cub3d))
		return (FAIL);
	// Should we load/init the main level here and not start the same if there's an error?
	if (!init_floor(cub3d))
		return (FAIL);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	cub3d_t	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	if (init_game(&cub3d, av[1]))
		start_game(&cub3d);
	close_game(&cub3d);
	system("leaks cub3D");
	return (0);
}
