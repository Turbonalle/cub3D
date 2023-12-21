#include "../incl/cub3d.h"

void	delete_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		mlx_delete_image(cub3d->mlx, cub3d->hearts[i].full.img);
		mlx_delete_image(cub3d->mlx, cub3d->hearts[i].empty.img);
	}
}

void	disable_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].full.img->instances[i].enabled = FALSE;
		cub3d->hearts[i].empty.img->instances[i].enabled = FALSE;
	}
}

void	enable_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].full.img->instances[i].enabled = TRUE;
		cub3d->hearts[i].empty.img->instances[i].enabled = FALSE;
	}
}

void	adjust_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < cub3d->player.health)
	{
		cub3d->hearts[i].full.img->instances[i].enabled = TRUE;
		cub3d->hearts[i].empty.img->instances[i].enabled = FALSE;
	}
	while (i < HEARTS)
	{
		cub3d->hearts[i].full.img->instances[i].enabled = FALSE;
		cub3d->hearts[i].empty.img->instances[i].enabled = TRUE;
		i++;
	}
}
