#include "../incl/cub3d.h"

int	get_marker_pos(cub3d_t *cub3d)
{
	return (lerp(cub3d->pause_menu.sensitivity_slider.marker_min_pos,
		cub3d->pause_menu.sensitivity_slider.marker_max_pos,
		MOUSE_MIN_SENSITIVITY,
		MOUSE_MAX_SENSITIVITY,
		cub3d->settings.mouse_sensitivity) - SLIDER_MARKER_WIDTH / 2);
}

double	get_sensitivity(cub3d_t *cub3d)
{
	return (lerp(MOUSE_MIN_SENSITIVITY,
		MOUSE_MAX_SENSITIVITY,
		(double)cub3d->pause_menu.sensitivity_slider.marker_min_pos,
		(double)cub3d->pause_menu.sensitivity_slider.marker_max_pos,
		(double)cub3d->pause_menu.sensitivity_slider.marker->instances[0].x + SLIDER_MARKER_WIDTH / 2));
}

void	disable_pause_menu(mlx_t *mlx, pause_menu_t *menu)
{
	mlx_delete_image(mlx, menu->bg);
	mlx_delete_image(mlx, menu->menu);
	mlx_delete_image(mlx, menu->title.img);
	mlx_delete_image(mlx, menu->text_fps);
	mlx_delete_image(mlx, menu->text_fisheye);
	mlx_delete_image(mlx, menu->text_mouse);
	mlx_delete_image(mlx, menu->text_mouse_sensitivity);
	mlx_delete_image(mlx, menu->box_fps[0].text);
	mlx_delete_image(mlx, menu->box_fps[1].text);
	mlx_delete_image(mlx, menu->box_fps[2].text);
	mlx_delete_image(mlx, menu->box_fps[3].text);
	mlx_delete_image(mlx, menu->box_fisheye[0].text);
	mlx_delete_image(mlx, menu->box_fisheye[1].text);
	mlx_delete_image(mlx, menu->box_mouse[0].text);
	mlx_delete_image(mlx, menu->box_mouse[1].text);
	mlx_delete_image(mlx, menu->sensitivity_slider.marker);
}

int	enable_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	// create images
	menu->bg = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->bg)
		return (err("Failed to create image"));
	menu->menu = mlx_new_image(cub3d->mlx, cub3d->mlx->width * 0.5, cub3d->mlx->height * 0.9);
	if (!menu->menu)
		return (err("Failed to create image"));
	menu->title.img = mlx_texture_to_image(cub3d->mlx, menu->title.texture);
	if (!menu->title.img)
		return (err("Failed to create image"));
	menu->sensitivity_slider.marker = mlx_new_image(cub3d->mlx, SLIDER_MARKER_WIDTH, SLIDER_MARKER_HEIGHT);
	if (!menu->sensitivity_slider.marker)
		return (err("Failed to create image"));

	// put images to window
	if (mlx_image_to_window(cub3d->mlx, menu->bg, 0, 0) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(cub3d->mlx, menu->menu, menu->menu_pos.x, menu->menu_pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(cub3d->mlx, menu->title.img, menu->title.pos.x, menu->title.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(cub3d->mlx, menu->sensitivity_slider.marker, get_marker_pos(cub3d), menu->sensitivity_slider.marker_pos.y) < 0)
		return (err("Failed to put image to window"));
	
	// draw images
	draw_background(menu->bg, set_transparency(PAUSE_MENU_BACKGROUND_COLOR, PAUSE_MENU_TRANSPARENCY));
	draw_background(menu->menu, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->menu);
	draw_slider(menu->menu, &menu->sensitivity_slider);
	
	// add text
	add_category_text(cub3d, menu);
	add_checkbox_text(cub3d, menu);
	return (SUCCESS);
}
