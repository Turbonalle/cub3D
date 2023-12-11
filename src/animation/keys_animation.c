#include "../incl/cub3d.h"

void    disable_frames_except(mlx_image_t **frames, int except)
{
    int i;

    printf("disable_frames_except called, exception is %d\n", except);
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
            //cub3d->level->key_groups[i].frames[(curr_frame_num + 24 - 1) % 24]->instances[0].enabled = false;
            //cub3d->level->key_groups[i].frames[curr_frame_num]->instances[0].enabled = true;
            //disable_frames_except(cub3d->level->key_groups[i].frames, curr_frame_num);
            //all_frames_to_window(cub3d, cub3d->level->key_groups[i].frames);
            disable_frames_except(cub3d->level->key_groups[i].frames, curr_frame_num);
            /* mlx_image_to_window(cub3d->mlx, cub3d->level->key_groups[i].frames[curr_frame_num], 100, 100);cub3d->level->key_groups[i].frames[curr_frame_num]->instances[0].enabled = false;
            cub3d->level->key_groups[i].frames[0]->instances[0].enabled = false;
            cub3d->level->key_groups[i].frames[0]->instances[0].enabled = false;
            cub3d->level->key_groups[i].frames[0]->instances[0].enabled = false; */
            // TODO: improve to disable all frames
        }
        i++;
    }
}

/* void    disable_frames_except(mlx_image_t **frames, int except)
{
    int i;

    printf("disable_frames_except called\n");
    i = 0;
    while (i < NUM_FRAMES_KEY)
    {
        printf("i = %d\n", i);
        if (i != except)
            frames[i]->instances[0].enabled = false;
        else
            frames[i]->instances[0].enabled = true;
    }
}

void    draw_animated_keys(cub3d_t *cub3d)
{
    int i;
    int curr_frame_num;

    printf("draw_animated_keys called\n");
    i = 0;
    while (i < NUM_DOORS_MAX)
    {
        if (cub3d->level->key_groups[i].num_keys_total > 0)
        {
            printf("run_time: %f, divided byy %f : %f, after mod: %d\n", cub3d->run_time, ANIMATION_INTERVAL_MS, cub3d->run_time / ANIMATION_INTERVAL_MS, (int)(cub3d->run_time / ANIMATION_INTERVAL_MS) % NUM_FRAMES_KEY);

            curr_frame_num = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS) % NUM_FRAMES_KEY;
            disable_frames_except(cub3d->level->key_groups[i].frames, i);
            printf("after disable_frames_except\n");
            mlx_image_to_window(cub3d->mlx, cub3d->level->key_groups[i].frames[curr_frame_num], 0, 0);
            // TODO: improve to disable all frames
            
        }
        i++;
    }
} */