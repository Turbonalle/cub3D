#include "../incl/cub3d.h"

void	mouse_game(cub3d_t *cub3d)
{
	if (hover_minimap(cub3d))
	{
		cub3d->on_minimap = TRUE;
		cub3d->mouse_set_pos.x = cub3d->mouse.x;
		cub3d->mouse_set_pos.y = cub3d->mouse.y;
		cub3d->orig_minimap_pos.x = cub3d->minimap.pos.x;
		cub3d->orig_minimap_pos.y = cub3d->minimap.pos.y;
	}
	else
		cub3d->on_minimap = FALSE;
}

void	mouse_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	vector_t	mouse;

	mlx_get_mouse_pos(cub3d->mlx, &mouse.x, &mouse.y);
	printf("mouse.x: %d, mouse.y: %d\n", mouse.x, mouse.y);
	printf("slider.pos.x: %d, slider.pos.y: %d\n", menu->sensitivity_slider.marker.pos.x, menu->sensitivity_slider.marker.pos.y);
	if (hover_any_box(cub3d, menu))
	{
		printf("clicked on box\n");
		update_pause_settings(cub3d, menu);
		print_settings(cub3d);
	}
	if (hover_rectangle(cub3d, &menu->sensitivity_slider.marker))
	{

		printf("clicked on sensitivity slider\n");
		menu->sensitivity_slider.marker_state = TRUE;
		// cub3d->mouse_set_pos.x = cub3d->mouse.x;
		// cub3d->mouse_set_pos.y = cub3d->mouse.y;
		// menu->sensitivity_slider.orig_marker_pos.x = menu->sensitivity_slider.marker.pos.x;
		// menu->sensitivity_slider.orig_marker_pos.y = menu->sensitivity_slider.marker.pos.y;
		menu->sensitivity_slider.marker.pos.x = mouse.x - menu->sensitivity_slider.marker.width / 2;
		if (menu->sensitivity_slider.marker.pos.x < menu->sensitivity_slider.marker_min_pos)
			menu->sensitivity_slider.marker.pos.x = menu->sensitivity_slider.marker_min_pos;
		else if (menu->sensitivity_slider.marker.pos.x > menu->sensitivity_slider.marker_max_pos)
			menu->sensitivity_slider.marker.pos.x = menu->sensitivity_slider.marker_max_pos;
	}
	else
		menu->sensitivity_slider.marker_state = FALSE;
}

void	mouse_intro(cub3d_t *cub3d)
{
	if (hover_image(cub3d, cub3d->intro.img))
	{
		cub3d->level = &cub3d->levels[0];
		if (!load_level(cub3d, cub3d->level))
			return ;
		disable_intro(cub3d);
		cub3d->settings.e_behaviour = cub3d->player.num_completed % 3;
		cub3d->settings.e_speed = cub3d->player.num_completed / 3;
		cub3d->intro_watched = TRUE;
		cub3d->state = STATE_GAME;
		handle_cursor(cub3d);
		start_timer(cub3d);
	}
}