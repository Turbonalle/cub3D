#include "../../incl/cub3d.h"

void	free_info(char **info)
{
	int	i;

	i = -1;
	if (info)
	{
		while (info[++i])
			free(info[i]);
		free(info);
	}
}

void	free_list(map_node_t *head)
{
	map_node_t	*temp;

	while (head)
	{
		temp = head->next;
		free(head->line);
		free(head);
		head = temp;
	}
}

void	free_record(record_t *record)
{
	if (record)
	{
		if (record->name)
			free(record->name);
		free(record);
	}
}

void	free_keys(key_node_t *head)
{
	key_node_t	*temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

void	free_doors(door_pos_t *head)
{
	door_pos_t	*temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

void	free_backup(level_t level)
{
	int	i;

	i = 0;
	while (level.backup[i])
	{
		free(level.backup[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		free(level.texture[i].path);
		i++;
	}
	free(level.backup);
}

static void	delete_textures(cub3d_t *cub3d, int i)
{
	free(cub3d->leaderboard.rect_level);
	free(cub3d->leaderboard.text_level);
	mlx_delete_texture(cub3d->start_menu.title.texture);
	mlx_delete_texture(cub3d->start_menu.exit.texture);
	mlx_delete_texture(cub3d->start_menu.start.texture);
	mlx_delete_texture(cub3d->start_menu.level.texture);
	mlx_delete_texture(cub3d->start_menu.exit_hover.texture);
	mlx_delete_texture(cub3d->start_menu.start_hover.texture);
	mlx_delete_texture(cub3d->start_menu.level_hover.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_exit.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_start.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_level.texture);
	mlx_delete_texture(cub3d->level_menu.title.texture);
	mlx_delete_texture(cub3d->level_menu.back.texture);
	mlx_delete_texture(cub3d->level_menu.leaderboard.texture);
	mlx_delete_texture(cub3d->level_menu.back_hover.texture);
	mlx_delete_texture(cub3d->level_menu.leaderboard_hover.texture);
	while (i < 8)
	{
		mlx_delete_texture(cub3d->level_menu.minilevels[i].number.texture);
		i++;
	}
}

void	free_cub3d(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i <= 9)
	{
		free_list(cub3d->levels[i].map_list);
		i++;
	}
	free(cub3d->rays);
	i = 0;
	while (i <= 9)
	{
		free_backup(cub3d->levels[i]);
		i++;
	}
	i = 0;
	while (i < NUM_FRAMES_ENEMY_IDLE)
	{
		mlx_delete_texture(cub3d->frames_idle[i]);
		mlx_delete_texture(cub3d->frames_walking[i]);
		i++;
	}
	free(cub3d->levels);
	delete_textures(cub3d, 0);
}

void	free_level(cub3d_t *cub3d)
{
	int	i;
	int	j;
	key_node_t  *tmp;

	free_info(cub3d->level->map);
	if (cub3d->num_enemies)
	{
		i = 0;
		while (i < cub3d->num_enemies)
		{
			cub3d->enemy[i].img_curr_frame->instances[0].enabled = FALSE;
			i++;
		}
		free(cub3d->enemy);
	}
	i = 0;
	mlx_delete_texture(cub3d->level->heart.texture);
	mlx_delete_texture(cub3d->level->heart_half.texture);
	mlx_delete_texture(cub3d->level->heart_empty.texture);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_img);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_half_img);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_empty_img);
	while (i < NUM_DOORS_MAX)
	{
		free_doors(cub3d->level->door_groups[i].door_positions);
		if (cub3d->level->key_groups[i].num_keys_total)
		{
			tmp = cub3d->level->key_groups[i].keys;
			while (tmp)
			{
				tmp->img_curr_frame->instances[0].enabled = FALSE;
				tmp = tmp->next;
			}
			mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[i].img_text_key_count);
			mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[i].img_key_icon);
			free_keys(cub3d->level->key_groups[i].keys);
			j = 0;
			while (j < NUM_FRAMES_KEY)
			{
				mlx_delete_texture(cub3d->level->key_groups[i].textures_frames[j]);
				j++;
			}
			free(cub3d->level->key_groups[i].textures_frames);
		}
		j = 0;
		while (j < cub3d->num_enemies)
		{
			mlx_delete_image(cub3d->mlx, cub3d->enemy[j].img_curr_frame);
			j++;
		}
		mlx_delete_texture(cub3d->level->key_groups[i].texture_key_icon);
		i++;
	}
}
