#include "../incl/cub3d.h"

void	free_textures_before_failed_old(texture_t *textures, int failed_index)
{
	int	i;

	printf("DELETE TEXTURES and paths free_textures_before_failed\n");
	i = 0;
	while (i < failed_index)
	{
		printf("Freeing texture %d with path %s\n", i, textures[i].path);
		free(textures[i].path);
		mlx_delete_texture(textures[i].texture);
		textures[i].path = NULL;
		textures[i].texture = NULL;
		printf("Freed texture %d\n", i);
		i++;
	}
}

int	init_textures(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub3d->level->texture[i].texture = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		printf("Loading texture %d, path: %s\n", i, cub3d->level->texture[i].path);
		cub3d->level->texture[i].texture = mlx_load_png(cub3d->level->texture[i].path);
		if (!cub3d->level->texture[i].texture)
		{
			printf("Failed to load texture %d\n", i);
			free_textures_before_failed(cub3d->level->texture, i);
			return (err("Failed to load texture"));
		}
		printf("Loaded texture %d\n", i);
		i++;
	}
	return (SUCCESS);
}
