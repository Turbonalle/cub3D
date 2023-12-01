#include "../incl/cub3d.h"

int	hover_button(cub3d_t *cub3d, button_t *button)
{
	int mouse_x;
	int mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	return (mouse_x >= button->pos.x
		&& mouse_x <= button->pos.x + button->width
		&& mouse_y >= button->pos.y
		&& mouse_y <= button->pos.y + button->height);
}

int hover_rectangle(cub3d_t *cub3d, rectangle_t *rect)
{
	int mouse_x;
	int mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	return (mouse_x >= rect->pos.x
		&& mouse_x <= rect->pos.x + rect->width
		&& mouse_y >= rect->pos.y
		&& mouse_y <= rect->pos.y + rect->height);
}

int hover_box(cub3d_t *cub3d, box_t *box)
{
	int mouse_x;
	int mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	return (mouse_x >= box->pos.x
		&& mouse_x <= box->pos.x + box->size
		&& mouse_y >= box->pos.y
		&& mouse_y <= box->pos.y + box->size);
}

int hover_any_box(cub3d_t *cub3d, pause_menu_t *menu)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (hover_box(cub3d, &menu->box_fps[i]))
			return (TRUE);
	}
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_fisheye[i]))
			return (TRUE);
	}
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_mouse[i]))
			return (TRUE);
	}
	return (FALSE);
}
