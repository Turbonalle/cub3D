#include "../incl/cub3d.h"

static int	count_not_collected_visible_keys(key_node_t	*keys)
{
	int	count;

	count = 0;
	while (keys)
	{
		if (keys->collected == FALSE && keys->visible == TRUE)
			count++;
		keys = keys->next;
	}
	return (count);
}

static int	count_all_not_collected_visible_keys(cub3d_t *cub3d)
{
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		count += count_not_collected_visible_keys(cub3d->level->key_groups[i].keys);
		i++;
	}
	return (count);
}

static void	sort_keys_by_dist_to_player(key_node_t **keys)
{
	int			i;
	int			j;
	key_node_t	*tmp;

	i = 0;
	while (keys[i])
	{
		j = i + 1;
		while (keys[j])
		{
			if (keys[i]->dist_to_player < keys[j]->dist_to_player)
			{
				tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void fill_keys_array(cub3d_t *cub3d, key_node_t **keys)
{
	int			i;
	int			j;
	key_node_t	*tmp;

	i = 0;
	j = 0;
	while (i < NUM_DOORS_MAX)
	{
		tmp = cub3d->level->key_groups[i].keys;
		while (tmp)
		{
			if (tmp->collected == FALSE && tmp->visible == TRUE)
			{
				keys[j] = tmp;
				j++;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

key_node_t	**create_array_of_keys_ordered_by_dist(cub3d_t *cub3d)
{
	key_node_t	**keys;
	int			count;

	count = count_all_not_collected_visible_keys(cub3d);
	keys = malloc(sizeof(key_node_t *) * (count + 1));
    if (!keys)
        return(NULL);
	keys[count] = NULL;
	fill_keys_array(cub3d, keys);
	sort_keys_by_dist_to_player(keys);
	return (keys);
}
