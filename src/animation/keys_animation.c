#include "../incl/cub3d.h"

mlx_image_t *scale_img(cub3d_t *cub3d, mlx_image_t *img, double factor)
{
    mlx_image_t *scaled_img;

    scaled_img = mlx_new_image(cub3d->mlx, img->width * factor, img->height * factor);
    mlx_scale_image(img, scaled_img);
    return (scaled_img);
}

void    disable_frames_except(mlx_image_t **img_frames, int except, int instance_index)
{
    int i;

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

double  calculate_scale_factor(cub3d_t *cub3d, dvector_t key_pos, dvector_t player_pos)
{
    double  dist;
    double  scale_factor;

    dist = sqrt(pow(key_pos.x - player_pos.x, 2) + pow(key_pos.y - player_pos.y, 2));
    scale_factor = dist / KEY_NORMAL_SCALE_DISTANCE;
    return (scale_factor);
}

void    draw_keys(cub3d_t *cub3d, int group_index, int curr_frame_num)
{
    key_node_t  *tmp;
    double scale_factor;

    tmp = cub3d->level->key_groups[group_index].keys;
    while (tmp)
    {
        if (tmp->collected == false)
        {
            scale_factor = calculate_scale_factor(cub3d, tmp->pos, cub3d->player.pos);
            tmp->img_curr_frame = scale_img(cub3d, cub3d->level->key_groups[group_index].img_frames[curr_frame_num], scale_factor);
            mlx_image_to_window(cub3d->mlx, tmp->img_curr_frame, tmp->pos_world.x, tmp->pos_world.y);
        }
        tmp = tmp->next;
    }
}

void    draw_animated_keys(cub3d_t *cub3d)
{
    int i;

    i = 0;
    while (i < NUM_DOORS_MAX)
    {
        if (cub3d->level->key_groups[i].num_keys_total > 0)
        {
            /* printf("run_time: %f, divided byy %f : %f, after mod: %d\n", cub3d->run_time, ANIMATION_INTERVAL_MS * 1000, cub3d->run_time / ANIMATION_INTERVAL_MS * 1000, (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_KEY); */
            cub3d->level->key_groups[i].curr_frame_index = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_KEY;
            draw_keys(cub3d, i, cub3d->level->key_groups[i].curr_frame_index);
            //disable_frames_except(cub3d->level->key_groups[i].img_frames, curr_frame_num, valid_key_group_index);
            // TODO: improve to disable only necessary frames
        }
        i++;
    }
}
