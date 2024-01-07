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
	if (hover_any_box(cub3d, menu))
	{
		update_pause_settings(cub3d, menu);
		print_settings(cub3d);
	}
	if (hover_image(cub3d, menu->sensitivity_slider.marker))
	{
		printf("clicked on sensitivity slider\n");
		menu->sensitivity_slider.on_marker = TRUE;
		menu->sensitivity_slider.marker_orig_pos = cub3d->mouse.x;
	}
	else
		menu->sensitivity_slider.on_marker = FALSE;
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