#include "../incl/cub3d.h"

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

void update(void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
	mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse.x, &cub3d->mouse.y);
	if (cub3d->keys.mouse_left && hover_minimap(cub3d))
	{
		printf(TERMINAL_GREEN);
		printf("mouse = [%d, %d]\n", cub3d->mouse.x, cub3d->mouse.y);
		printf("mouse_set_pos = [%d, %d]\n", cub3d->mouse_set_pos.x, cub3d->mouse_set_pos.y);
		printf("orig_minimap_pos = [%d, %d]\n", cub3d->orig_minimap_pos.x, cub3d->orig_minimap_pos.y);
		printf(TERMINAL_RESET);
		
		vector_t mouse_moved;
		mouse_moved.x = cub3d->mouse.x - cub3d->mouse_set_pos.x;
		mouse_moved.y = cub3d->mouse.y - cub3d->mouse_set_pos.y;
		if (cub3d->orig_minimap_pos.x + mouse_moved.x < 0)
		{
			printf(TERMINAL_RED"x < 0\n"TERMINAL_RESET);
			cub3d->minimap.pos.x = 0;
		}
		else if (cub3d->orig_minimap_pos.x + mouse_moved.x + cub3d->minimap.width > WIDTH)
		{
			printf(TERMINAL_RED"x + width > WIDTH\n"TERMINAL_RESET);
			cub3d->minimap.pos.x = WIDTH - cub3d->minimap.width;
		}
		else
		{
			printf(TERMINAL_YELLOW"x is OK!\n"TERMINAL_RESET);
			cub3d->minimap.pos.x = cub3d->orig_minimap_pos.x + mouse_moved.x;
		}
		if (cub3d->orig_minimap_pos.y + mouse_moved.y < 0)
			cub3d->minimap.pos.y = 0;
		else if (cub3d->orig_minimap_pos.y + mouse_moved.y + cub3d->minimap.height > HEIGHT)
			cub3d->minimap.pos.y = HEIGHT - cub3d->minimap.height;
		else
			cub3d->minimap.pos.y = cub3d->orig_minimap_pos.y + mouse_moved.y;
	}
	player_movement(cub3d);
	draw_background(cub3d);
	// raycasting(cub3d);
	minimap(cub3d);
}

void start_game(cub3d_t *cub3d)
{
	mlx_close_hook(cub3d->mlx, &handle_close_window, cub3d->mlx);
	mlx_key_hook(cub3d->mlx, &get_input, cub3d);
	mlx_scroll_hook(cub3d->mlx, &hook_mouse_scroll, cub3d);
	mlx_mouse_hook(cub3d->mlx, &hook_mouse_buttons, cub3d);
	mlx_loop_hook(cub3d->mlx, &update, cub3d);
	mlx_loop(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
}