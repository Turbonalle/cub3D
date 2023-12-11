#include "../incl/cub3d.h"



void    disable_frames_except(mlx_image_t **frames, int except)
{
    int i;

    //printf("disable_frames_except called, exception is %d\n", except);
    i = 0;
    while (i < NUM_FRAMES_KEY)
    {
        if (i != except)
            frames[i]->instances[0].enabled = false;
        else
            frames[i]->instances[0].enabled = true;
        i++;
    }
}

void    draw_animated_keys(cub3d_t *cub3d)
{
    int i;
    int curr_frame_num;

    i = 0;
    while (i < NUM_DOORS_MAX)
    {
        if (cub3d->level->key_groups[i].num_keys_total > 0)
        {
            /* printf("run_time: %f, divided byy %f : %f, after mod: %d\n", cub3d->run_time, ANIMATION_INTERVAL_MS * 1000, cub3d->run_time / ANIMATION_INTERVAL_MS * 1000, (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_KEY); */
            curr_frame_num = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_KEY;
            disable_frames_except(cub3d->level->key_groups[i].frames, curr_frame_num);
            // TODO: improve to disable only necessary frames
        }
        i++;
    }
}
