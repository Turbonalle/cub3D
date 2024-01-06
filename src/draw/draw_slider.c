#include "../incl/cub3d.h"

// void	move_slider_marker(cub3d_t *cub3d)		// Change to marker
// {
// 	vector_t	mouse_moved;

// 	mouse_moved.x = cub3d->mouse.x - cub3d->mouse_set_pos.x;
// 	mouse_moved.y = cub3d->mouse.y - cub3d->mouse_set_pos.y;
// 	if (cub3d->orig_minimap_pos.x + mouse_moved.x < 0)
// 		cub3d->minimap.img->instances[0].x = 0;
// 	else if (cub3d->orig_minimap_pos.x + mouse_moved.x + cub3d->minimap.width > (int)cub3d->img->width)
// 		cub3d->minimap.img->instances[0].x = cub3d->img->width - cub3d->minimap.width;
// 	else
// 		cub3d->minimap.img->instances[0].x = cub3d->orig_minimap_pos.x + mouse_moved.x;
// 	if (cub3d->orig_minimap_pos.y + mouse_moved.y < 0)
// 		cub3d->minimap.img->instances[0].y = 0;
// 	else if (cub3d->orig_minimap_pos.y + mouse_moved.y + cub3d->minimap.height > (int)cub3d->img->height)
// 		cub3d->minimap.img->instances[0].y = cub3d->img->height - cub3d->minimap.height;
// 	else
// 		cub3d->minimap.img->instances[0].y = cub3d->orig_minimap_pos.y + mouse_moved.y;
// 	cub3d->minimap.pos.x = cub3d->minimap.img->instances[0].x;
// 	cub3d->minimap.pos.y = cub3d->minimap.img->instances[0].y;
// }

void	round_slider_edges(mlx_image_t *img, slider_t *slider, int end_length)
{
	draw_circle(img,
		slider->pos.x,
		slider->pos.y - end_length / 2,
		SLIDER_LINE_WIDTH / 2,
		SLIDER_LINE_COLOR);
	draw_circle(img,
		slider->pos.x,
		slider->pos.y + end_length / 2,
		SLIDER_LINE_WIDTH / 2,
		SLIDER_LINE_COLOR);
	draw_circle(img,
		slider->pos.x + slider->length - SLIDER_LINE_WIDTH,
		slider->pos.y - end_length / 2,
		SLIDER_LINE_WIDTH / 2,
		SLIDER_LINE_COLOR);
	draw_circle(img,
		slider->pos.x + slider->length - SLIDER_LINE_WIDTH,
		slider->pos.y + end_length / 2,
		SLIDER_LINE_WIDTH / 2,
		SLIDER_LINE_COLOR);
}

void	draw_slider_line(mlx_image_t *img, slider_t *slider)
{
	int		x;
	int		y;

	y = slider->pos.y - 1;
	while (++y < slider->pos.y + SLIDER_LINE_WIDTH)
	{
		x = slider->pos.x - 1;
		while (++x < slider->pos.x + slider->length)
			mlx_put_pixel(img, x, y, SLIDER_LINE_COLOR);
	}
}

void	draw_slider_ends(mlx_image_t *img, slider_t *slider)
{
	int		x;
	int		y;

	y = slider->pos.y + SLIDER_LINE_WIDTH / 2 - SLIDER_MARKER_HEIGHT / 2 - 1;
	while (++y < slider->pos.y + SLIDER_LINE_WIDTH / 2 + SLIDER_MARKER_HEIGHT / 2)
	{
		x = slider->pos.x - 1;
		while (++x < slider->pos.x + SLIDER_LINE_WIDTH)
			mlx_put_pixel(img, x, y, SLIDER_LINE_COLOR);
		x = slider->pos.x - 1 + slider->length - SLIDER_LINE_WIDTH;
		while (++x < slider->pos.x + slider->length)
			mlx_put_pixel(img, x, y, SLIDER_LINE_COLOR);
	}
	// round_slider_edges(img, slider, SLIDER_MARKER_HEIGHT);
}

void	draw_slider_marker(mlx_image_t *img, slider_t *slider)
{
	int	marker_pos;

	marker_pos = (int)lerp(slider->marker_min_pos, slider->marker_max_pos, MOUSE_MIN_SENSITIVITY, MOUSE_MAX_SENSITIVITY, slider->value);
	slider->marker.pos.x = marker_pos - slider->marker.width / 2;
	slider->marker.pos.y = slider->pos.y + SLIDER_LINE_WIDTH / 2 - slider->marker.height / 2;
	draw_rectangle(img, &slider->marker);
}

void	draw_slider(mlx_image_t *img, slider_t *slider)
{
	draw_slider_line(img, slider);
	draw_slider_ends(img, slider);
	draw_slider_marker(img, slider);
}