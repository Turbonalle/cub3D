#include "../incl/raycaster.h"

void hook_keytest(mlx_key_data_t keydata, void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
	if (keydata.key == MLX_KEY_DELETE && keydata.action == MLX_PRESS)
	{
		reset_map(cub3d->img, cub3d->map);
	}
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(cub3d->mlx);
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

void hook_lmb_pressed(void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
	if (cub3d->lmb_pressed)
		empty_chosen_box(cub3d->mlx, cub3d->img, cub3d->map, BG_COLOR);
}

//------------------------------------------------------------------------------

void hook_rmb_pressed(void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
	if (cub3d->rmb_pressed)
		fill_chosen_box(cub3d->mlx, cub3d->img, cub3d->map, WALL_COLOR);
}

//------------------------------------------------------------------------------

void hook_mouse_buttons(enum mouse_key key, enum action action, enum modifier_key modifier, void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
    (void)modifier;

    if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
    {
        printf("Left button pressed!\n");
		cub3d->lmb_pressed = TRUE;
    }
    else if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
    {
        printf("Left button released!\n");
		cub3d->lmb_pressed = FALSE;
		print_map(cub3d->map);
    }
    else if (key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
    {
		printf("Right button pressed!\n");
		cub3d->rmb_pressed = TRUE;
    }
    else if (key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
    {
        printf("Right button released!\n");
		cub3d->rmb_pressed = FALSE;
		print_map(cub3d->map);
	}
}
