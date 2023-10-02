#include "../incl/cub3d.h"

void get_input(mlx_key_data_t *keydata, cub3d_t *cub3d)
{
	if (keydata->key == MLX_KEY_W && keydata->action == MLX_PRESS)
		cub3d->keys.w = TRUE;
	else if (keydata->key == MLX_KEY_A && keydata->action == MLX_PRESS)
		cub3d->keys.a = TRUE;
	else if (keydata->key == MLX_KEY_S && keydata->action == MLX_PRESS)
		cub3d->keys.s = TRUE;
	else if (keydata->key == MLX_KEY_D && keydata->action == MLX_PRESS)
		cub3d->keys.d = TRUE;
	else if (keydata->key == MLX_KEY_LEFT && keydata->action == MLX_PRESS)
		cub3d->keys.left = TRUE;
	else if (keydata->key == MLX_KEY_RIGHT && keydata->action == MLX_PRESS)
		cub3d->keys.right = TRUE;
	else if (keydata->key == MLX_KEY_W && keydata->action == MLX_RELEASE)
		cub3d->keys.w = FALSE;
	else if (keydata->key == MLX_KEY_A && keydata->action == MLX_RELEASE)
		cub3d->keys.a = FALSE;
	else if (keydata->key == MLX_KEY_S && keydata->action == MLX_RELEASE)
		cub3d->keys.s = FALSE;
	else if (keydata->key == MLX_KEY_D && keydata->action == MLX_RELEASE)
		cub3d->keys.d = FALSE;
	else if (keydata->key == MLX_KEY_LEFT && keydata->action == MLX_RELEASE)
		cub3d->keys.left = FALSE;
	else if (keydata->key == MLX_KEY_RIGHT && keydata->action == MLX_RELEASE)
		cub3d->keys.right = FALSE;
}

void draw_background(cub3d_t *cub3d)
{
	int row;
	int column;

	row = -1;
	while (++row < HEIGHT)
	{
		column = -1;
		while (++column < WIDTH)
		{
			if (row < HEIGHT / 2)
				mlx_put_pixel(cub3d->img, column, row, cub3d->ceiling_color);
			else
				mlx_put_pixel(cub3d->img, column, row, cub3d->floor_color);
		}
	}
}

void update(mlx_key_data_t keydata, void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
	handle_escape_key(&keydata, cub3d->mlx);
	get_input(&keydata, cub3d);
	player_movement(cub3d);
	// draw_background(cub3d);
	// raycasting(cub3d);
	minimap(cub3d);
}

void start_game(cub3d_t *cub3d)
{
	printf("start_game\n");
	// draw_background(cub3d);
	// raycasting(cub3d);
	minimap(cub3d);
	mlx_close_hook(cub3d->mlx, &handle_close_window, cub3d->mlx);
	mlx_key_hook(cub3d->mlx, &update, cub3d);
	mlx_loop(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
}