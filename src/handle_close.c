#include "../incl/cub3d.h"

void handle_close_window(void *param)
{
	mlx_t *mlx;

	mlx = param;
	mlx_close_window(mlx);
}

void handle_escape_key(mlx_key_data_t *keydata, mlx_t *mlx)
{
	if (keydata->key == MLX_KEY_ESCAPE && keydata->action == MLX_PRESS)
		mlx_close_window(mlx);
}