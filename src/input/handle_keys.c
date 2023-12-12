#include "../incl/cub3d.h"

void	handle_keypresses(mlx_key_data_t keydata, cub3d_t *cub3d)
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
		if (cub3d->state == STATE_PAUSE)
		{
			delete_pause_menu(cub3d);
			cub3d->state = STATE_GAME;
			continue_timer(cub3d);
		}
		else if (cub3d->state == STATE_GAME)
		{
			pause_timer(cub3d);
			draw_pause_menu(cub3d, &cub3d->pause_menu);
			cub3d->state = STATE_PAUSE;
		}
	}
	else if (keydata.key == MLX_KEY_T)
	{
		printf("Time passed: %f\n", mlx_get_time() - cub3d->start_timestamp);
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		if (cub3d->state == STATE_GAME)
		{
			printf("Back to start menu\n");
			free_info(cub3d->level->map);
			mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
			draw_start_menu(cub3d, &cub3d->start_menu);
			int i = -1;
			while (++i < NUM_DOORS_MAX)
			{
				mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[i].img_key_icon);
				mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[i].img_text_key_count);
				if (cub3d->level->key_groups[i].num_keys_total)
				{
					free(cub3d->level->key_groups[i].textures_frames);
					free(cub3d->level->key_groups[i].frames);
					free_keys(cub3d->level->key_groups[i].keys);
				}
				free_doors(cub3d->level->door_groups[i].door_positions);
			}
			// free enemies, keys, doors
			cub3d->state = STATE_START;
		}
		else if (cub3d->state == STATE_START)
		{
			mlx_close_window(cub3d->mlx);
		}
		else if (cub3d->state == STATE_LEVEL)
		{
			delete_level_menu(cub3d, &cub3d->level_menu);
			draw_start_menu(cub3d, &cub3d->start_menu);
			cub3d->state = STATE_START;
		}
		else if (cub3d->state == STATE_LEADERBOARD)
		{
			delete_leaderboard(cub3d, &cub3d->leaderboard);
			draw_level_menu(cub3d, &cub3d->level_menu);
			cub3d->state = STATE_LEVEL;
		}
		else if (cub3d->state == STATE_PAUSE)
		{
			delete_pause_menu(cub3d);
			cub3d->state = STATE_GAME;
			continue_timer(cub3d);
		}
		else if (cub3d->state == STATE_GAMEOVER)
		{
			// delete_gameover_menu(cub3d);
			draw_start_menu(cub3d, &cub3d->start_menu);
			cub3d->state = STATE_START;
		}
		else if (cub3d->state == STATE_SETTINGS)
		{
			// delete_settings_menu(cub3d, &cub3d->settings_menu);
			// draw_start_menu(cub3d, &cub3d->start_menu);
			cub3d->state = STATE_START;
		}
	}
}

void	handle_keyreleases(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_W)
		cub3d->keys.w = FALSE;
	else if (keydata.key == MLX_KEY_A)
		cub3d->keys.a = FALSE;
	else if (keydata.key == MLX_KEY_S)
		cub3d->keys.s = FALSE;
	else if (keydata.key == MLX_KEY_D)
		cub3d->keys.d = FALSE;
	else if (keydata.key == MLX_KEY_LEFT)
		cub3d->keys.left = FALSE;
	else if (keydata.key == MLX_KEY_RIGHT)
		cub3d->keys.right = FALSE;
	else if (keydata.key == MLX_KEY_UP)
		cub3d->keys.up = FALSE;
	else if (keydata.key == MLX_KEY_DOWN)
		cub3d->keys.down = FALSE;
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