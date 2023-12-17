#include "../incl/cub3d.h"

void scale_image(mlx_image_t *src, mlx_image_t *res, double factor)
{
	uint32_t	row_src;
	uint32_t	col_src;
	uint32_t	row_res;
	uint32_t	col_res;
	//int		pixel;	
	int i;

	row_res = 0;
	printf("factor: %f\n", factor);
	printf("RES height: %u, width: %u\n", res->height, res->width);
	while (row_res < res->height)
	{
		col_res = 0;
		while (col_res < res->width)
		{
			row_src = (uint32_t)(row_res / factor); // TODO: make proper rounding
			col_src = (uint32_t)(col_res / factor);
			//ft_memcpy(&pixel, src->pixels + row_src * src->width * 4 + col_src * 4, 4);
			//printf("res[%u, %u] = src[%u, %u]\n", row_res, col_res, row_src, col_src);
			//mlx_put_pixel(res, col_res, row_res, pixel);
			
			/* printf("[%u, %u] : res pixels[%u] = src pixels[%u]\n",
			row_res,
			col_res,
			row_res * res->width * 4 + col_res * 4,
			row_src * src->width * 4 + col_src * 4); */
			i = 0;
			while (i < 4)
			{
				
				res->pixels[row_res * res->width * 4 + col_res * 4 + i]
				= src->pixels[row_src * src->width * 4 + col_src * 4 + i];
				i++;
			}
			col_res++;
		}
		row_res++;
	}
}

mlx_image_t *scale_img(cub3d_t *cub3d, mlx_image_t *src, double factor)
{
	mlx_image_t	*res;

	res = mlx_new_image(cub3d->mlx, src->width * factor, src->height * factor);
	scale_image(src, res, factor);
	return (res);
}

void	disable_frames_except(mlx_image_t **img_frames, int except, int instance_index)
{
	int	i;

	//printf("disable_frames_except called, exception is %d\n", except);
	i = 0;
	while (i < NUM_FRAMES_KEY)
	{
		if (i != except)
			img_frames[i]->instances[instance_index].enabled = false;
		else
			img_frames[i]->instances[instance_index].enabled = true;
		i++;
	}
}

double	calculate_scale_factor(dvector_t key_pos, dvector_t player_pos)
{
	double	dist;
	double	scale_factor;

	dist = sqrt(pow(key_pos.x - player_pos.x, 2) + pow(key_pos.y - player_pos.y, 2));
	scale_factor = KEY_NORMAL_SCALE_DISTANCE / dist;
	return (scale_factor);
}

void	draw_keys(cub3d_t *cub3d, int group_index, int curr_frame_num)
{
	key_node_t  *tmp;
	double scale_factor;
	mlx_image_t	*old_img;

	printf("curr_frame_num: %i\n", curr_frame_num);
	tmp = cub3d->level->key_groups[group_index].keys;
	while (tmp)
	{
		if (tmp->collected == false)
		{
			printf("group_index: %i\n", group_index);
			
			scale_factor = calculate_scale_factor(tmp->pos, cub3d->player.pos);
			old_img = tmp->img_curr_frame;
			tmp->img_curr_frame = scale_img(cub3d,
				cub3d->level->key_groups[group_index].img_frames[curr_frame_num],
				scale_factor);
			
			mlx_image_to_window(cub3d->mlx, tmp->img_curr_frame, tmp->pos_world.x, tmp->pos_world.y);
			//mlx_image_to_window(cub3d->mlx, cub3d->level->key_groups[group_index].img_frames[curr_frame_num], tmp->pos_world.x, tmp->pos_world.y);
			mlx_delete_image(cub3d->mlx, old_img);
		}
		tmp = tmp->next;
	}
}

void	draw_animated_keys(cub3d_t *cub3d)
{
	int i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		if (cub3d->level->key_groups[i].num_keys_total > 0)
		{
			/* printf("run_time: %f, divided byy %f : %f, after mod: %d\n", cub3d->run_time, ANIMATION_INTERVAL_MS * 1000, cub3d->run_time / ANIMATION_INTERVAL_MS * 1000, (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_KEY); */

			// set current frame based on time
			cub3d->level->key_groups[i].curr_frame_index = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_KEY;
			if (cub3d->level->key_groups[i].prev_frame_index
				!= cub3d->level->key_groups[i].curr_frame_index)
			{
				draw_keys(cub3d, i, cub3d->level->key_groups[i].curr_frame_index);
				cub3d->level->key_groups[i].prev_frame_index
					= cub3d->level->key_groups[i].curr_frame_index;
			}
			

			//disable_frames_except(cub3d->level->key_groups[i].img_frames, curr_frame_num, valid_key_group_index);
			// TODO: improve to disable only necessary frames
		}
		i++;
	}
}
