#include "../incl/cub3d.h"

int	init_textures(cub3d_t *cub3d)
{
	int i;

	i = 0;
	while(i < 4)
	{
		cub3d->level->texture[i].texture = NULL;
		i++;
	}
	i = 0;
	while(i < 4)
	{
		printf("Loading texture %d\n", i);
		cub3d->level->texture[i].texture = mlx_load_png(cub3d->level->texture[i].path);
		if (!cub3d->level->texture[i].texture)
			return (err("Failed to load texture"));
		i++;
	}
	return (SUCCESS);
}