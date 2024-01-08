#include "../incl/cub3d.h"

// TODO: generic frames-to-image-array 

void	draw_door_open(cub3d_t *cub3d, int index)
{
	mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[index].img_text_key_count);
	
	cub3d->level->key_groups[index].img_text_key_count = mlx_put_string(
		cub3d->mlx,
		"open",
		cub3d->level->key_groups[index].key_icon_coords.x + cub3d->mlx->width * 0.03,
		cub3d->level->key_groups[index].key_icon_coords.y + cub3d->mlx->height * 0.01
	);
}
int	draw_key_count(cub3d_t *cub3d, int index)
{
	char	*text_collected;
	char	*text_collected_slash;
	char	*text_total;
	char	*text;

	
	text_collected = ft_itoa(cub3d->level->key_groups[index].num_keys_total - cub3d->level->door_groups[index].num_keys_left);
	if (!text_collected)
	{
		return (err("MALLOC fail in update_key_count"));
	}
	text_total = ft_itoa(cub3d->level->key_groups[index].num_keys_total);
	if (!text_total)
	{
		free(text_collected);
		return (err("MALLOC fail in update_key_count"));
	}
	text_collected_slash = ft_strjoin(text_collected, "/");
	if (!text_collected_slash)
	{
		free(text_collected);
		free(text_total);
		return (err("MALLOC fail in update_key_count"));
	}
	text = ft_strjoin(text_collected_slash, text_total);
	free(text_collected);
	free(text_collected_slash);
	free(text_total);
	if (!text)
	{
		return (err("MALLOC fail in update_key_count"));
	}
	if (cub3d->level->key_groups[index].img_text_key_count)
		mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[index].img_text_key_count);
	cub3d->level->key_groups[index].img_text_key_count = mlx_put_string(
		cub3d->mlx,
		text,
		cub3d->level->key_groups[index].key_icon_coords.x + cub3d->mlx->width * 0.03,
		cub3d->level->key_groups[index].key_icon_coords.y + cub3d->mlx->height * 0.01
	);
	free(text);
	return (1);
}

int draw_key_counts(cub3d_t *cub3d)
{
	int	index;

	index = 0;
	while (index < NUM_DOORS_MAX)
	{
		if (cub3d->level->key_groups[index].keys)
		{
			if (cub3d->level->door_groups[index].num_keys_left == 0)
					draw_door_open(cub3d, index);
			else
			{
				if (!draw_key_count(cub3d, index))
					return (0);
			}
		}
		index++;
	}
	return (1);
}
