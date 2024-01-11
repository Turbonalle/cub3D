#include "../incl/cub3d.h"

void	free_textures_before_failed(texture_t *textures, int failed_index)
{
	int	i;

	i = 0;
	while (i < failed_index)
	{
		printf("Freeing texture %d\n", i);
		// free(textures[i].path);
		mlx_delete_texture(textures[i].texture);
		printf("Freed texture %d\n", i);
		i++;
	}
}

int	init_door_textures(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub3d->door[i].texture = NULL;
		i++;
	}
	cub3d->door[0].texture = mlx_load_png(TEXTURE_DOOR_A);
	cub3d->door[1].texture = mlx_load_png(TEXTURE_DOOR_B);
	if (!cub3d->door[1].texture)
	{
		free_textures_before_failed(cub3d->door, 1);
		return (err("Failed to load texture"));
	}
	cub3d->door[2].texture = mlx_load_png(TEXTURE_DOOR_C);
	if (!cub3d->door[2].texture)
	{
		free_textures_before_failed(cub3d->door, 2);
		return (err("Failed to load texture"));
	}
	cub3d->door[3].texture = mlx_load_png(TEXTURE_DOOR_D);
	if (!cub3d->door[3].texture)
	{
		free_textures_before_failed(cub3d->door, 3);
		return (err("Failed to load texture"));
	}
	cub3d->door[4].texture = mlx_load_png(TEXTURE_DOOR_OPEN);
	if (!cub3d->door[4].texture)
	{
		free_textures_before_failed(cub3d->door, 4);
		return (err("Failed to load texture"));
	}
	return (SUCCESS);
}
