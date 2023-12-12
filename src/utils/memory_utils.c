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

void	free_cub3d(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		printf("freeing texture %d\n", i);
		if (cub3d->level->texture[i].path)
			free(cub3d->level->texture[i].path);
		// if (cub3d->texture[i].img)
		// 	free(cub3d->texture[i].img);
	}
	i = -1;
	printf("freeing map list\n");
	free_list(cub3d->level->map_list);
	printf("freeing rays\n");
	free(cub3d->rays);
	while (cub3d->level->map[++i])
	{
		printf("freeing map line %d\n", i);
		free(cub3d->level->map[i]);
	}
	if (cub3d->level->map)
	{
		printf("freeing map\n");
		free(cub3d->level->map);
	}
	if (cub3d->num_enemies)
	{
		printf("freeing enemies\n");
		free(cub3d->enemy);
	}
	i = -1;
	while (++i < NUM_DOORS_MAX)
	{
		printf("freeing key group %d\n", i);
		free_keys(cub3d->level->key_groups[i].keys);
		printf("freeing door group %d\n", i);
		free_doors(cub3d->level->door_groups[i].door_positions);
	}
	printf("deleting menus\n");
	delete_menus(cub3d);
}
