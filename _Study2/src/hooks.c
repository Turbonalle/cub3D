#include "../incl/raycaster.h"

void hook_keytest(mlx_key_data_t keydata, void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
	if (keydata.key == MLX_KEY_DELETE && keydata.action == MLX_PRESS)
		reset_map(cub3d->img, cub3d->map);
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cub3d->mlx);
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) && keydata.action == MLX_PRESS)
		cub3d->player.up = TRUE;
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) && keydata.action == MLX_RELEASE)
		cub3d->player.up = FALSE;
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) && keydata.action == MLX_PRESS)
		cub3d->player.down = TRUE;
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) && keydata.action == MLX_RELEASE)
		cub3d->player.down = FALSE;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		cub3d->player.left = TRUE;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		cub3d->player.left = FALSE;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		cub3d->player.right = TRUE;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		cub3d->player.right = FALSE;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		cub3d->player.rotate_left = TRUE;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		cub3d->player.rotate_left = FALSE;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		cub3d->player.rotate_right = TRUE;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		cub3d->player.rotate_right = FALSE;
	else if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		cub3d->q_pressed = TRUE;
	else if (keydata.key == MLX_KEY_Q && keydata.action == MLX_RELEASE)
		cub3d->q_pressed = FALSE;
	else if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
	{
		if (cub3d->rays == FALSE)
			cub3d->rays = TRUE;
		else
			cub3d->rays = FALSE;
	}
}

//------------------------------------------------------------------------------

void hook_mouse_scroll(double xdelta, double ydelta, void *param)
{
	(void)param;

	if (ydelta > 0)
		puts("Up!");
	else if (ydelta < 0)
		puts("Down!");

	if (xdelta < 0)
		puts("Left!");
	else if (xdelta > 0)
		puts("Right!");
}

//------------------------------------------------------------------------------

void hook_close(void *param)
{
	mlx_t *mlx;

	mlx = param;
	mlx_close_window(mlx);
}

//------------------------------------------------------------------------------

void hook_other_functions(void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
	if (cub3d->rmb_pressed)
		fill_chosen_box(cub3d->mlx, cub3d->img, cub3d->map, WALL_COLOR);
	else if (cub3d->lmb_pressed)
		empty_chosen_box(cub3d->mlx, cub3d->img, cub3d->map, BG_COLOR);
}

//------------------------------------------------------------------------------

void hook_mouse_buttons(enum mouse_key key, enum action action, enum modifier_key modifier, void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
    (void)modifier;

    if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
    {
		cub3d->lmb_pressed = TRUE;
    }
    else if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
    {
		cub3d->lmb_pressed = FALSE;
		print_map(cub3d->map);
		draw_player(cub3d);
    }
    else if (key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
    {
		cub3d->rmb_pressed = TRUE;
    }
    else if (key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
    {
		cub3d->rmb_pressed = FALSE;
		print_map(cub3d->map);
		draw_player(cub3d);
	}
}
