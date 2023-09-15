/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the current frame.
 */

/**
typedef struct mlx
{
	void*		window;
	void*		context;
	int			width;
	int			height;
	double		delta_time;
}	mlx_t;
*/

// Note: Compile MLX42 with -DDEBUG=1 to see assertions and to add debug flags. This can help you find critical mistakes during development!

#include "../incl/raycaster.h"

//------------------------------------------------------------------------------

// Exit the program as failure.
void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

//------------------------------------------------------------------------------

void init_cubed(cub3d_t *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Raycaster", true);
	if (!cub3d->mlx)
		ft_error();
	cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img || (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0))
		ft_error();
	cub3d->map = init_map(cub3d->img, 30, 30, 16);
	cub3d->lmb_pressed = FALSE;
	cub3d->rmb_pressed = FALSE;
}

//------------------------------------------------------------------------------

int	main(void)
{
	cub3d_t cub3d;

	init_cubed(&cub3d);

	draw_background(cub3d.img, BG_COLOR);
	draw_wall_border(cub3d.img, cub3d.map, WALL_COLOR);

	print_map(cub3d.map);

	mlx_close_hook(cub3d.mlx, &hook_close, cub3d.mlx);
	mlx_key_hook(cub3d.mlx, &hook_keytest, &cub3d);
	mlx_scroll_hook(cub3d.mlx, &hook_mouse_scroll, NULL);
	mlx_mouse_hook(cub3d.mlx, &hook_mouse_buttons, &cub3d);
	mlx_loop_hook(cub3d.mlx, &hook_lmb_pressed, &cub3d);
	mlx_loop_hook(cub3d.mlx, &hook_rmb_pressed, &cub3d);
	
	mlx_loop(cub3d.mlx);
	mlx_terminate(cub3d.mlx);
	free_map(cub3d.map);
	return (EXIT_SUCCESS);
}
