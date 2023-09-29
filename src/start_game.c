#include "../incl/cub3d.h"

void handle_exit(void *param)
{
	mlx_t *mlx;

	mlx = param;
	mlx_close_window(mlx);
}

void handle_keys(mlx_key_data_t keydata, void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cub3d->mlx);
}

void start_game(cub3d_t *cub3d)
{
	mlx_close_hook(cub3d->mlx, &handle_exit, cub3d->mlx);
	mlx_key_hook(cub3d->mlx, &handle_keys, cub3d);
	mlx_loop(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
}