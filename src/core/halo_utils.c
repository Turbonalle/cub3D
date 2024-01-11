#include "../incl/cub3d.h"

int	init_halo(cub3d_t *cub3d)
{
	cub3d->halo.img = mlx_new_image(cub3d->mlx,
			cub3d->img->width,
			cub3d->img->height);
	if (!cub3d->halo.img
		|| (mlx_image_to_window(cub3d->mlx, cub3d->halo.img, 0, 0) < 0))
		return (err("Failed to create halo image"));
	cub3d->halo.img->instances[0].enabled = FALSE;
	cub3d->halo.active = FALSE;
	cub3d->halo.color = 0;
	cub3d->halo.timestamp = 0;
	return (1);
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
	//printf("halo_is_active\n");
	/* printf("halo->timestamp: %f\n", halo->timestamp);
	printf("mlx_get_time(): %f\n", mlx_get_time());
	printf("time_delta: %f\n", mlx_get_time() - halo->timestamp);
	printf("HALO_TIME: %d\n", HALO_TIME); */
	return (mlx_get_time() - halo->timestamp < HALO_TIME);
}

void	handle_halo(halo_t *halo)
{
	//printf("halo pointer: %p\n", halo);
	if (halo->active)
	{
		//printf("halo->active\n");
		if (halo_is_active(halo))
		{
			//printf("before drawing halo\n");
			draw_halo(halo->img, halo);
			//printf("after drawing halo\n");
		}
		else
		{
			///printf("before enabling halo\n");
			//printf("halo->img: %p\n", halo->img);
			//printf("halo->img->instances: %p\n", halo->img->instances);
			//printf("halo->img->instances[0].enabled: %d\n", halo->img->instances[0].enabled);
			halo->img->instances[0].enabled = FALSE;
			//printf("after enabling halo\n");
			halo->active = FALSE;
			//printf("after setting halo to inactive\n");
		}
	}
	//printf("handle_halo end\n");
}
