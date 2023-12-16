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
	if (cub3d->num_enemies)
		free(cub3d->enemy);
	free(cub3d->levels);
	free(cub3d->leaderboard.rect_level);
	free(cub3d->leaderboard.text_level);
}
