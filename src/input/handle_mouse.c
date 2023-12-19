#include "../incl/cub3d.h"

void hook_mouse_buttons(enum mouse_key key, enum action action, enum modifier_key modifier, void *param)
{
	cub3d_t *cub3d;

	cub3d = param;
    (void)modifier;

	if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		cub3d->keys.mouse_left = TRUE;
		if (cub3d->state == STATE_GAME && cub3d->settings.mouse == FALSE) // added check if settings.mouse is off, to prevent player from moving minimap (and let program use mouse_set_pos for player rotation with mouse)
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
		else if (cub3d->state == STATE_PAUSE)
		{
			if (hover_any_box(cub3d, &cub3d->pause_menu))
				update_pause_settings(cub3d, &cub3d->pause_menu);
		}
		else if (cub3d->state == STATE_START)
		{
			if (hover_button(cub3d, &cub3d->start_menu.button_start))
			{
				cub3d->level = &cub3d->levels[0];
				if (!load_level(cub3d, cub3d->level))
					return ;
				disable_start_menu(&cub3d->start_menu);
				cub3d->state = STATE_GAME;
				handle_cursor(cub3d);
				start_timer(cub3d);
			}
			else if (hover_button(cub3d, &cub3d->start_menu.button_level))
			{
				cub3d->state = STATE_LEVEL;
				disable_start_menu(&cub3d->start_menu);
				enable_level_menu(&cub3d->level_menu);
			}
			// else if (hover_button(cub3d, &cub3d->start_menu.button_settings))
			// {
			// 	cub3d->state = STATE_SETTINGS;
			// 	mlx_destroy_image(cub3d->mlx, cub3d->start_menu.img);
			// 	init_settings(cub3d);
			// }
			else if (hover_button(cub3d, &cub3d->start_menu.button_exit))
				mlx_close_window(cub3d->mlx);
		}
		else if (cub3d->state == STATE_LEVEL)
		{
			int i;

			i = -1;
			while (++i < cub3d->n_levels - 1)
			{
				if (hover_button(cub3d, &cub3d->level_menu.buttons[i]))
				{
					cub3d->level = &cub3d->levels[i + 1];
					if (!load_level(cub3d, &cub3d->levels[i + 1]))
						return ;
					cub3d->speedrun = TRUE;
					cub3d->state = STATE_GAME;
					disable_level_menu(&cub3d->level_menu);
					handle_cursor(cub3d);
					start_timer(cub3d);
				}
			}
			if (hover_button(cub3d, &cub3d->level_menu.button_back))
			{
				disable_level_menu(&cub3d->level_menu);
				enable_start_menu(&cub3d->start_menu);
				cub3d->state = STATE_START;
			}
			if (hover_button(cub3d, &cub3d->level_menu.button_leaderboard))
			{
				disable_level_menu(&cub3d->level_menu);
				enable_leaderboard(cub3d, &cub3d->leaderboard);
				cub3d->state = STATE_LEADERBOARD;
			}
		}
		else if (cub3d->state == STATE_LEADERBOARD)
		{
			if (hover_button(cub3d, &cub3d->leaderboard.button_back))
			{
				disable_leaderboard(cub3d, &cub3d->leaderboard);
				enable_level_menu(&cub3d->level_menu);
				cub3d->state = STATE_LEVEL;
			}
		}
		else if (cub3d->state == STATE_GAMEOVER)
		{
			if (hover_button(cub3d, &cub3d->gameover_menu.button_exit))
			{
				disable_gameover_menu(&cub3d->gameover_menu);
				enable_start_menu(&cub3d->start_menu);
				cub3d->state = STATE_START;
			}
			if (hover_button(cub3d, &cub3d->gameover_menu.button_restart))
			{
				// if (cub3d->level == &cub3d->levels[0])
				// 	cub3d->speedrun = FALSE;
				// else
				// 	cub3d->speedrun = TRUE;
				if (!load_level(cub3d, cub3d->level))
					return ;
				disable_gameover_menu(&cub3d->gameover_menu);
				cub3d->state = STATE_GAME;
				handle_cursor(cub3d);
				start_timer(cub3d);
			}
		}
	}
    else if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		cub3d->keys.mouse_left = FALSE;
    else if (key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		cub3d->keys.mouse_right = TRUE;
    else if (key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
		cub3d->keys.mouse_right = FALSE;
}

void hook_mouse_scroll(double xdelta, double ydelta, void *param)
{
	cub3d_t *cub3d;

	(void)xdelta;
	cub3d = param;
	if (ydelta > 0 && hover_minimap(cub3d))
		zoom_in_minimap(cub3d);
	else if (ydelta < 0 && hover_minimap(cub3d))
		zoom_out_minimap(cub3d);
}
