#include "../../incl/cub3d.h"

void	free_backup(level_t level)
{
	int	i;

	i = 0;
	while (level.backup[i])
	{
		free(level.backup[i]);
		level.backup[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		free(level.texture[i].path);
		level.texture[i].path = NULL;
		mlx_delete_texture(level.texture[i].texture);
		level.texture[i].texture = NULL;
		i++;
	}
	free(level.backup);
	level.backup = NULL;
}

void	delete_heart(cub3d_t *cub3d)
{
	mlx_delete_texture(cub3d->level->heart.texture);
	mlx_delete_texture(cub3d->level->heart_half.texture);
	mlx_delete_texture(cub3d->level->heart_empty.texture);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_img);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_half_img);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_empty_img);
	cub3d->level->heart.texture = NULL;
	cub3d->level->heart_half.texture = NULL;
	cub3d->level->heart_empty.texture = NULL;
	cub3d->level->heart_img = NULL;
	cub3d->level->heart_half_img = NULL;
	cub3d->level->heart_empty_img = NULL;
}

void	free_key_and_door_groups(cub3d_t *cub3d, int i)
{
	int			j;
	key_node_t	*tmp;

	free_doors(cub3d->level->door_groups[i].door_positions);
	cub3d->level->door_groups[i].door_positions = NULL;
	mlx_delete_texture(cub3d->level->key_groups[i].texture_key_icon);
	cub3d->level->key_groups[i].texture_key_icon = NULL;
	if (cub3d->level->key_groups[i].num_keys_total)
	{
		tmp = cub3d->level->key_groups[i].keys;
		while (tmp)
		{
			//printf("deleting key img_curr_frame image. pointer: %p\n", tmp->img_curr_frame);
			// TODO: change this to delete image
			//mlx_delete_image(cub3d->mlx, tmp->img_curr_frame);
			tmp->img_curr_frame->instances[0].enabled = FALSE;
			tmp = tmp->next;
		}
		mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[i].img_text_key_count);
		cub3d->level->key_groups[i].img_text_key_count = NULL;
		mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[i].img_key_icon);
		cub3d->level->key_groups[i].img_key_icon = NULL;
		free_keys(cub3d->level->key_groups[i].keys);
		cub3d->level->key_groups[i].keys = NULL;
		j = 0;
		while (j < NUM_FRAMES_KEY)
		{
			mlx_delete_texture(cub3d->level->key_groups[i].textures_frames[j]);
			cub3d->level->key_groups[i].textures_frames[j] = NULL;
			j++;
		}
		free(cub3d->level->key_groups[i].textures_frames);
		cub3d->level->key_groups[i].textures_frames = NULL;
	}
}

void	free_keys_and_doors(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		free_key_and_door_groups(cub3d, i);
		i++;
	}
}

void	free_level_textures(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if(cub3d->level->texture[i].texture)
			mlx_delete_texture(cub3d->level->texture[i].texture);
		cub3d->level->texture[i].texture = NULL;
		i++;
	}
}

void	free_enemies(cub3d_t *cub3d)
{
	int	i;

	if (cub3d->num_enemies)
	{
		i = 0;
		while (i < cub3d->num_enemies)
		{
			mlx_delete_image(cub3d->mlx, cub3d->enemy[i].img_curr_frame);
			//cub3d->enemy[i++].img_curr_frame->instances[0].enabled = FALSE;
			cub3d->enemy[i].img_curr_frame = NULL;
			i++;
		}
		free(cub3d->enemy);
		cub3d->enemy = NULL;
		cub3d->num_enemies = 0;
	}
}

void	free_distractions(cub3d_t *cub3d)
{
	int	i;

	if (cub3d->level->num_distractions)
	{
		i = 0;
		while (i < cub3d->level->num_distractions)
		{
			mlx_delete_image(cub3d->mlx, cub3d->level->distractions[i].img_distraction);
			cub3d->level->distractions[i].img_distraction = NULL;
			i++;
		}
		free(cub3d->level->distractions);
		cub3d->level->distractions = NULL;
	}
}

void	disable_items(cub3d_t *cub3d)
{
	cub3d->halo.img->instances[0].enabled = FALSE;
	disable_shroom(cub3d);
	disable_hearts(cub3d);
}


void	free_minimap(cub3d_t *cub3d)
{
	mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
}

void	free_level(cub3d_t *cub3d)
{
	free_keys_and_doors(cub3d);
	//free_level_textures(cub3d);
	free_info(cub3d->level->map);
	free_enemies(cub3d);
	free_distractions(cub3d);
	free_minimap(cub3d);
	disable_items(cub3d);
}

void	free_level_without_textures(cub3d_t *cub3d)
{
	printf("freeing level without textures START\n");
	free_keys_and_doors(cub3d);
	//printf("freed keys and doors\n");
	free_info(cub3d->level->map);
	//printf("freed info\n");
	free_enemies(cub3d);
	//printf("freed enemies\n");
	free_distractions(cub3d);
	//printf("freed distractions\n");
	free_minimap(cub3d);
	//printf("freed minimap\n");
	disable_items(cub3d);
	printf("freeing level without textures DONE\n");
}
