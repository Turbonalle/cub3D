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

void	free_delete_textures(level_t *level)
{
	int	i;

	printf("DELETING TEXTURES and paths free_delete_textures\n");
	i = 0;
	while (i < 4)
	{
		if (level->texture[i].path)
			free(level->texture[i].path);
		level->texture[i].path = NULL;
		if (level->texture[i].texture)
			mlx_delete_texture(level->texture[i].texture);
		level->texture[i].texture = NULL;
		i++;
	}
}
