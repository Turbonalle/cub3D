#include "../incl/cub3d.h"

void	disable_intro(cub3d_t *cub3d)
{
	cub3d->intro.img[0].enabled = FALSE;
}

void	enable_intro(cub3d_t *cub3d)
{
	cub3d->intro.img[0].enabled = TRUE;
}