#include "../../incl/cub3d.h"

void	delete_texture(texture_t *texture)
{
	if (texture->path)
		free(texture->path);
	if (texture->texture)
		mlx_delete_texture(texture->texture);
}

void	delete_png(mlx_t *mlx, png_t *png)
{
	if (png->img)
		mlx_delete_image(mlx, png->img);
	if (png->texture)
		mlx_delete_texture(png->texture);
}

void	free_pointer(void *ptr)
{
	if (ptr)
		free(ptr);
}