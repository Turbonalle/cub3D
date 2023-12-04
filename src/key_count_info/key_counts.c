#include "../incl/cub3d.h"

void	update_key_count(cub3d_t *cub3d, int index, int num_keys_already_drawn)
{
	//mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[index].img_key_count);
	//printf("update_key_count\n");
	/* printf("img_key_count: %p\n", cub3d->level->key_groups[index].img_key_count);
	draw_circle(cub3d->level->key_groups[index].img_key_count, 50, 70 + (50 * num_keys_already_drawn), 10, get_door_key_color(cub3d, index)); */
	//printf("circle position:%d, %d\n", 100, 100 + (100 * num_keys_already_drawn));
	draw_circle(cub3d->level->key_groups[index].img_key_count,
		cub3d->mlx->width * 0.05,
		cub3d->mlx->height * 0.9 - cub3d->mlx->height * 0.05 * num_keys_already_drawn,
		cub3d->mlx->height * 0.01,
		get_door_key_color(cub3d, index));

	//printf("circle drawn\n");
	// TODO: text
	/* cub3d->level->key_groups[index].img_key_count = mlx_put_string(cub3d->mlx,
		cub3d->level->key_groups[index].text_key_count,
		cub3d->mlx->width * 0.05 + cub3d->mlx->height * 0.05,
		cub3d->mlx->height - cub3d->mlx->width * 0.05 - cub3d->mlx->height * 0.1 * num_keys_already_drawn); */
}

void	update_key_counts(cub3d_t *cub3d)
{
	int	num_keys_already_drawn;
	int	index;

	num_keys_already_drawn = 0;
	index = 0;
	//printf("update_key_counts\n");
	while (index < NUM_DOORS_MAX)
	{
		//printf("index:%i\n", index);
		if (cub3d->level->key_groups[index].keys)
		{
			//printf("keys at index:%i exist\n", index);
			update_key_count(cub3d, index, num_keys_already_drawn);
			num_keys_already_drawn++;
		}
		index++;
	}
}

void draw_key_counts(cub3d_t *cub3d)
{
	//printf("draw_key_counts\n");
	update_key_counts(cub3d);
	/* cub3d->level->key_groups[index].img_key_count = mlx_put_string(cub3d->mlx,
		cub3d->level->key_groups[index].text_key_count,
		cub3d->level->key_groups[index].pos_key_count.x,
		cub3d->level->key_groups[index].pos_key_count.y); */
}