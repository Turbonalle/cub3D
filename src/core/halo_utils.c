#include "../incl/cub3d.h"

void	init_halo(cub3d_t *cub3d, halo_t *halo)
{
	halo->img = mlx_new_image(cub3d->mlx,
			cub3d->img->width,
			cub3d->img->height);
	if (!halo->img || (mlx_image_to_window(cub3d->mlx, halo->img, 0, 0) < 0))
		err("Failed to create halo image");
	halo->img->instances[0].enabled = FALSE;
	halo->active = FALSE;
	halo->color = 0;
	halo->timestamp = 0;
}

void	activate_halo(halo_t *halo, int color)
{
	halo->img->instances[0].enabled = TRUE;
	halo->active = TRUE;
	halo->color = color;
	halo->timestamp = mlx_get_time();
}

static int	halo_is_active(halo_t *halo)
{
	return (mlx_get_time() - halo->timestamp < HALO_TIME);
}

void	handle_halo(halo_t *halo)
{
	if (halo->active)
	{
		if (halo_is_active(halo))
		{
			printf("halo is active!\n");
			draw_halo(halo->img, halo);
		}
			
		else
		{
			halo->img->instances[0].enabled = FALSE;
			halo->active = FALSE;
		}
	}
}
