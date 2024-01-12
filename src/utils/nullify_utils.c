#include "../incl/cub3d.h"

void	nullify_png(png_t *png)
{
	png->img = NULL;
	png->texture = NULL;
}

void	nullify_texture(texture_t *texture)
{
	texture->path = NULL;
	texture->texture = NULL;
}
