#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void	delete_pause_menu(cub3d_t *cub3d)
{
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.img);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.text_title);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.text_fps);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.text_fisheye);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.text_mouse);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.box_fps[0].text);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.box_fps[1].text);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.box_fps[2].text);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.box_fps[3].text);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.box_fisheye[0].text);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.box_fisheye[1].text);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.box_mouse[0].text);
	mlx_delete_image(cub3d->mlx, cub3d->pause_menu.box_mouse[1].text);
}

//------------------------------------------------------------------------------

void draw_pause_menu_background(cub3d_t *cub3d, pause_menu_t *menu)
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

//------------------------------------------------------------------------------

void draw_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	menu->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->img)
		err("Failed to create pause menu image");
		
	draw_pause_menu_background(cub3d, menu);
	draw_rectangle(menu->img, &menu->rect_title);
	draw_checkbox(cub3d, &menu->box_fps[0]);
	draw_checkbox(cub3d, &menu->box_fps[1]);
	draw_checkbox(cub3d, &menu->box_fps[2]);
	draw_checkbox(cub3d, &menu->box_fps[3]);
	draw_checkbox(cub3d, &menu->box_fisheye[0]);
	draw_checkbox(cub3d, &menu->box_fisheye[1]);
	draw_checkbox(cub3d, &menu->box_mouse[0]);
	draw_checkbox(cub3d, &menu->box_mouse[1]);
	
	mlx_image_to_window(cub3d->mlx, cub3d->pause_menu.img, 0, 0);
	
	add_title_text(cub3d, menu);
	add_category_text(cub3d, menu);
	add_checkbox_text(cub3d, menu);
}
