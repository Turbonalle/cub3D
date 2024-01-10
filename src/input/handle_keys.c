#include "../incl/cub3d.h"

void	handle_name_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_LEFT_SHIFT || keydata.key == MLX_KEY_RIGHT_SHIFT)
	{
		cub3d->keys.shift = TRUE;
		return ;
	}
	cub3d->name_menu.changed = TRUE;
	if (keydata.key == MLX_KEY_Q)
		cub3d->keys.q = TRUE;
	else if (keydata.key == MLX_KEY_W)
		cub3d->keys.w = TRUE;
	else if (keydata.key == MLX_KEY_E)
		cub3d->keys.e = TRUE;
	else if (keydata.key == MLX_KEY_R)
		cub3d->keys.r = TRUE;
	else if (keydata.key == MLX_KEY_T)
		cub3d->keys.t = TRUE;
	else if (keydata.key == MLX_KEY_Y)
		cub3d->keys.y = TRUE;
	else if (keydata.key == MLX_KEY_U)
		cub3d->keys.u = TRUE;
	else if (keydata.key == MLX_KEY_I)
		cub3d->keys.i = TRUE;
	else if (keydata.key == MLX_KEY_O)
		cub3d->keys.o = TRUE;
	else if (keydata.key == MLX_KEY_P)
		cub3d->keys.p = TRUE;
	else if (keydata.key == MLX_KEY_A)
		cub3d->keys.a = TRUE;
	else if (keydata.key == MLX_KEY_S)
		cub3d->keys.s = TRUE;
	else if (keydata.key == MLX_KEY_D)
		cub3d->keys.d = TRUE;
	else if (keydata.key == MLX_KEY_F)
		cub3d->keys.f = TRUE;
	else if (keydata.key == MLX_KEY_G)
		cub3d->keys.g = TRUE;
	else if (keydata.key == MLX_KEY_H)
		cub3d->keys.h = TRUE;
	else if (keydata.key == MLX_KEY_J)
		cub3d->keys.j = TRUE;
	else if (keydata.key == MLX_KEY_K)
		cub3d->keys.k = TRUE;
	else if (keydata.key == MLX_KEY_L)
		cub3d->keys.l = TRUE;
	else if (keydata.key == MLX_KEY_Z)
		cub3d->keys.z = TRUE;
	else if (keydata.key == MLX_KEY_X)
		cub3d->keys.x = TRUE;
	else if (keydata.key == MLX_KEY_C)
		cub3d->keys.c = TRUE;
	else if (keydata.key == MLX_KEY_V)
		cub3d->keys.v = TRUE;
	else if (keydata.key == MLX_KEY_B)
		cub3d->keys.b = TRUE;
	else if (keydata.key == MLX_KEY_N)
		cub3d->keys.n = TRUE;
	else if (keydata.key == MLX_KEY_M)
		cub3d->keys.m = TRUE;
	else if (keydata.key == MLX_KEY_SPACE)
		cub3d->keys.space = TRUE;
	else if (keydata.key == MLX_KEY_BACKSPACE)
		cub3d->keys.backspace = TRUE;
	else if (keydata.key == MLX_KEY_ENTER)
		cub3d->keys.enter = TRUE;
	else if (keydata.key == MLX_KEY_ESCAPE)
		cub3d->keys.escape = TRUE;
}

void	handle_game_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_W)
		cub3d->keys.w = TRUE;
	else if (keydata.key == MLX_KEY_A)
		cub3d->keys.a = TRUE;
	else if (keydata.key == MLX_KEY_S)
		cub3d->keys.s = TRUE;
	else if (keydata.key == MLX_KEY_D)
		cub3d->keys.d = TRUE;
	else if (keydata.key == MLX_KEY_LEFT)
		cub3d->keys.left = TRUE;
	else if (keydata.key == MLX_KEY_RIGHT)
		cub3d->keys.right = TRUE;
	else if (keydata.key == MLX_KEY_UP)
		cub3d->keys.up = TRUE;
	else if (keydata.key == MLX_KEY_DOWN)
		cub3d->keys.down = TRUE;
	else if (keydata.key == MLX_KEY_P)
	{
		pause_timer(cub3d);
		enable_pause_menu(cub3d, &cub3d->pause_menu);
		cub3d->state = STATE_PAUSE;
		handle_cursor(cub3d);
	}
	else if (keydata.key == MLX_KEY_T)
	{
		printf("Time passed: %f\n", mlx_get_time() - cub3d->start_timestamp);
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		printf("Back to start menu\n");
		if (cub3d->player.thrown)
		{
			cub3d->level->distractions[cub3d->level->num_distractions].img_distraction->instances[0].enabled = FALSE;
		}
		mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
		mlx_delete_image(cub3d->mlx, cub3d->timer.img_time);
		free_level(cub3d);
		if (cub3d->speedrun)
		{
			enable_level_menu(&cub3d->level_menu);
			cub3d->speedrun = FALSE;
			cub3d->state = STATE_LEVEL;
		}
		else
		{
			enable_start_menu(&cub3d->start_menu);
			cub3d->speedrun = FALSE;
			cub3d->state = STATE_START;
		}
		handle_cursor(cub3d);
	}
	else if (keydata.key == MLX_KEY_SPACE)
	{
		if (cub3d->player.mushroom_count > 0)
			cause_distraction(cub3d);
		else
			printf("You have no mushroom to throw\n");
	}
	else if (keydata.key == MLX_KEY_G)
		{

			if (cub3d->player.is_dirty_cheater < 2)
			cub3d->player.is_dirty_cheater++;
			else if (cub3d->player.is_dirty_cheater == 2)
			cub3d->player.is_dirty_cheater--;
		}
}

void	handle_pause_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_P || keydata.key == MLX_KEY_ESCAPE)
	{
		disable_pause_menu(cub3d->mlx, &cub3d->pause_menu);
		cub3d->state = STATE_GAME;
		handle_cursor(cub3d);
		continue_timer(cub3d);
	}
}

void	handle_start_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cub3d->mlx);
}

void	handle_level_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		disable_level_menu(&cub3d->level_menu);
		enable_start_menu(&cub3d->start_menu);
		cub3d->state = STATE_START;
	}
}

void	handle_leaderboard_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		disable_leaderboard(cub3d, &cub3d->leaderboard);
		enable_level_menu(&cub3d->level_menu);
		cub3d->state = STATE_LEVEL;
	}
}

void	handle_gameover_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		disable_gameover_menu(cub3d->mlx, &cub3d->gameover_menu);
		enable_start_menu(&cub3d->start_menu);
		cub3d->state = STATE_START;
	}
}

void	handle_intro_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_ENTER)
	{
		cub3d->level = &cub3d->levels[0];
		if (!load_level(cub3d, cub3d->level))
		{
			printf("handle_intro_input: Failed to load level\n");
			// TODO: add error message here, letting user know level failed to load
			disable_intro(cub3d);
			enable_start_menu(&cub3d->start_menu);
			cub3d->state = STATE_START;
			return ;
		}
		disable_intro(cub3d);
		cub3d->settings.e_behaviour = cub3d->player.num_completed % 3;
		cub3d->settings.e_speed = cub3d->player.num_completed / 3;
		cub3d->intro_watched = TRUE;
		cub3d->state = STATE_GAME;
		handle_cursor(cub3d);
		start_timer(cub3d);
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		disable_intro(cub3d);
		enable_start_menu(&cub3d->start_menu);
		cub3d->state = STATE_START;
	}
}

void	handle_keypresses(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (cub3d->state == STATE_GAME)
		handle_game_input(keydata, cub3d);
	else if (cub3d->state == STATE_ENTERNAME)
		handle_name_input(keydata, cub3d);
	else if (cub3d->state == STATE_PAUSE)
		handle_pause_input(keydata, cub3d);
	else if (cub3d->state == STATE_START)
		handle_start_input(keydata, cub3d);
	else if (cub3d->state == STATE_LEVEL)
		handle_level_input(keydata, cub3d);
	else if (cub3d->state == STATE_LEADERBOARD)
		handle_leaderboard_input(keydata, cub3d);
	else if (cub3d->state == STATE_GAMEOVER)
		handle_gameover_input(keydata, cub3d);
	else if (cub3d->state == STATE_INTRO)
		handle_intro_input(keydata, cub3d);
}

void	handle_keyreleases(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	cub3d->printed = FALSE;		// DEBUG
	if (keydata.key == MLX_KEY_Q)
		cub3d->keys.q = FALSE;
	else if (keydata.key == MLX_KEY_W)
		cub3d->keys.w = FALSE;
	else if (keydata.key == MLX_KEY_E)
		cub3d->keys.e = FALSE;
	else if (keydata.key == MLX_KEY_R)
		cub3d->keys.r = FALSE;
	else if (keydata.key == MLX_KEY_T)
		cub3d->keys.t = FALSE;
	else if (keydata.key == MLX_KEY_Y)
		cub3d->keys.y = FALSE;
	else if (keydata.key == MLX_KEY_U)
		cub3d->keys.u = FALSE;
	else if (keydata.key == MLX_KEY_I)
		cub3d->keys.i = FALSE;
	else if (keydata.key == MLX_KEY_O)
		cub3d->keys.o = FALSE;
	else if (keydata.key == MLX_KEY_P)
		cub3d->keys.p = FALSE;
	else if (keydata.key == MLX_KEY_A)
		cub3d->keys.a = FALSE;
	else if (keydata.key == MLX_KEY_S)
		cub3d->keys.s = FALSE;
	else if (keydata.key == MLX_KEY_D)
		cub3d->keys.d = FALSE;
	else if (keydata.key == MLX_KEY_F)
		cub3d->keys.f = FALSE;
	else if (keydata.key == MLX_KEY_G)
		cub3d->keys.g = FALSE;
	else if (keydata.key == MLX_KEY_H)
		cub3d->keys.h = FALSE;
	else if (keydata.key == MLX_KEY_J)
		cub3d->keys.j = FALSE;
	else if (keydata.key == MLX_KEY_K)
		cub3d->keys.k = FALSE;
	else if (keydata.key == MLX_KEY_L)
		cub3d->keys.l = FALSE;
	else if (keydata.key == MLX_KEY_Z)
		cub3d->keys.z = FALSE;
	else if (keydata.key == MLX_KEY_X)
		cub3d->keys.x = FALSE;
	else if (keydata.key == MLX_KEY_C)
		cub3d->keys.c = FALSE;
	else if (keydata.key == MLX_KEY_V)
		cub3d->keys.v = FALSE;
	else if (keydata.key == MLX_KEY_B)
		cub3d->keys.b = FALSE;
	else if (keydata.key == MLX_KEY_N)
		cub3d->keys.n = FALSE;
	else if (keydata.key == MLX_KEY_M)
		cub3d->keys.m = FALSE;
	else if (keydata.key == MLX_KEY_LEFT)
		cub3d->keys.left = FALSE;
	else if (keydata.key == MLX_KEY_RIGHT)
		cub3d->keys.right = FALSE;
	else if (keydata.key == MLX_KEY_UP)
		cub3d->keys.up = FALSE;
	else if (keydata.key == MLX_KEY_DOWN)
		cub3d->keys.down = FALSE;
	else if (keydata.key == MLX_KEY_SPACE)
		cub3d->keys.space = FALSE;
	else if (keydata.key == MLX_KEY_BACKSPACE)
		cub3d->keys.backspace = FALSE;
	else if (keydata.key == MLX_KEY_LEFT_SHIFT || keydata.key == MLX_KEY_RIGHT_SHIFT)
		cub3d->keys.shift = FALSE;
	else if (keydata.key == MLX_KEY_ENTER)
		cub3d->keys.enter = FALSE;
	else if (keydata.key == MLX_KEY_ESCAPE)
		cub3d->keys.escape = FALSE;
}

void	get_input(mlx_key_data_t keydata, void *param)
{
	cub3d_t	*cub3d;

	cub3d = param;
	if (keydata.action == MLX_PRESS)
		handle_keypresses(keydata, cub3d);
	else if (keydata.action == MLX_RELEASE)
		handle_keyreleases(keydata, cub3d);
}