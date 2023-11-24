#include "../incl/cub3d.h"

void set_menu_background(cub3d_t *cub3d, pause_menu_t *menu)
{
	unsigned int	row;
	unsigned int	column;

	row = -1;
	while (++row < cub3d->img->height)
	{
		column = -1;
		while (++column < cub3d->img->width)
			mlx_put_pixel(cub3d->pause_menu.img, column, row, menu->background_color);
	}
}

void init_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	cub3d->pause_menu.background_color = MENU_COLOR_BACKGROUND;
	menu->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->img)
		err("Failed to create pause menu image");
	set_menu_background(cub3d, menu);

	// menu->e_difficulty_text = mlx_put_string(cub3d->mlx, "Enemy Difficulty:", 100, 250);
	// menu->minimap_view_text = mlx_put_string(cub3d->mlx, "    Minimap View:", 100, 300);
}