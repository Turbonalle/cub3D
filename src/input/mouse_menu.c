#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void	mouse_start_menu(cub3d_t *cub3d)
{
	if (hover_image(cub3d, cub3d->start_menu.exit.img))
		mlx_close_window(cub3d->mlx);
	else if (hover_image(cub3d, cub3d->start_menu.start.img))
	{
		if (cub3d->intro_watched == FALSE)
		{
			disable_start_menu(&cub3d->start_menu);
			enable_intro(cub3d);
			cub3d->state = STATE_INTRO;
		}
		else
		{
			cub3d->level = &cub3d->levels[0];
			if (!load_level(cub3d, cub3d->level))
				return ;
			disable_start_menu(&cub3d->start_menu);
			cub3d->settings.e_behaviour = cub3d->player.num_completed % 3;
			cub3d->settings.e_speed = cub3d->player.num_completed / 3;
			printf("Level started, e_speed is %i, e_beh is %i\n",cub3d->settings.e_speed, cub3d->settings.e_behaviour);
			cub3d->state = STATE_GAME;
			handle_cursor(cub3d);
			start_timer(cub3d);
		}
	}
	else if (hover_image(cub3d, cub3d->start_menu.level.img))
	{
		cub3d->state = STATE_LEVEL;
		disable_start_menu(&cub3d->start_menu);
		enable_level_menu(&cub3d->level_menu);
	}
}

//------------------------------------------------------------------------------

void	mouse_level_menu(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < cub3d->n_levels)
	{
		if (hover_image(cub3d, cub3d->level_menu.minilevels[i].img))
		{
			cub3d->level = &cub3d->levels[i + 1];
			if (!load_level(cub3d, &cub3d->levels[i + 1]))
				return ;
			cub3d->speedrun = TRUE;
			cub3d->state = STATE_GAME;
			cub3d->settings.e_behaviour = STATIONARY;
			cub3d->settings.e_speed = 1;
			disable_level_menu(&cub3d->level_menu);
			handle_cursor(cub3d);
			start_timer(cub3d);
		}
	}
	if (hover_image(cub3d, cub3d->level_menu.back.img))
	{
		disable_level_menu(&cub3d->level_menu);
		enable_start_menu(&cub3d->start_menu);
		cub3d->state = STATE_START;
	}
	if (hover_image(cub3d, cub3d->level_menu.leaderboard.img))
	{
		disable_level_menu(&cub3d->level_menu);
		enable_leaderboard(cub3d, &cub3d->leaderboard);
		cub3d->state = STATE_LEADERBOARD;
	}
}

//------------------------------------------------------------------------------

void	mouse_gameover_menu(cub3d_t *cub3d, gameover_menu_t *menu)
{
	if (hover_image(cub3d, menu->back.img))
	{
		disable_gameover_menu(cub3d->mlx, menu);
		enable_start_menu(&cub3d->start_menu);
		cub3d->state = STATE_START;
		cub3d->speedrun = FALSE;
	}
	if (hover_image(cub3d, menu->restart.img))
	{
		if (!load_level(cub3d, cub3d->level))
			return ;
		disable_gameover_menu(cub3d->mlx, menu);
		cub3d->settings.e_behaviour = cub3d->player.num_completed % 3;
		cub3d->settings.e_speed = cub3d->player.num_completed / 3;
		printf("Level started, e_speed is %i, e_beh is %i\n",cub3d->settings.e_speed, cub3d->settings.e_behaviour);
		cub3d->state = STATE_GAME;
		handle_cursor(cub3d);
		start_timer(cub3d);
	}
}

//------------------------------------------------------------------------------

void	mouse_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	if (hover_image(cub3d, board->back.img))
	{
		disable_leaderboard(cub3d, board);
		enable_level_menu(&cub3d->level_menu);
		cub3d->state = STATE_LEVEL;
	}
}

//------------------------------------------------------------------------------

void	mouse_entername_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	if (hover_image(cub3d, menu->back.img))
	{
		disable_name_menu(cub3d->mlx, menu);
		enable_level_menu(&cub3d->level_menu);
		cub3d->state = STATE_LEVEL;
		cub3d->name_menu.changed = FALSE;
		cub3d->speedrun = FALSE;
	}
}