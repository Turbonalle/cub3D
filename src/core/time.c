#include "../incl/cub3d.h"

double	elapsed_time(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->start_timestamp);
}

double	elapsed_frame_time(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->frame_start_timestamp);
}

void	handle_fps(cub3d_t *cub3d)
{
	while (elapsed_frame_time(cub3d) < cub3d->frame_time)
		;
	cub3d->frame_start_timestamp = mlx_get_time();
}

void	set_fps(double *frame_time, int fps)
{
	*frame_time = 1.0 / (double)fps;
}

void	start_timer(cub3d_t *cub3d)
{
	cub3d->run_time = 0;
	cub3d->pause_timestamp = 0;
	cub3d->frame_time = 1.0 / (double)cub3d->settings.fps;
	cub3d->start_timestamp = mlx_get_time();
	cub3d->frame_start_timestamp = cub3d->start_timestamp;
}

double	paused_time(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->pause_timestamp);
}

void	pause_timer(cub3d_t *cub3d)
{
	cub3d->pause_timestamp = mlx_get_time();
}

void	continue_timer(cub3d_t *cub3d)
{
	cub3d->start_timestamp += paused_time(cub3d);
	cub3d->frame_start_timestamp = cub3d->start_timestamp;	// Needed or not?
}

void	update_timer(cub3d_t *cub3d)
{
	int minutes;
	int seconds;
	int hundredths;
	char *minutes_str;
	char *seconds_str;
	char *hundredths_str;

	cub3d->run_time = elapsed_time(cub3d);
	minutes = (int)cub3d->run_time / 60;
	seconds = (int)cub3d->run_time % 60;
	hundredths = (int)(cub3d->run_time * 100) % 100;
	if (minutes < 10)
		minutes_str = ft_strjoin("0", ft_itoa(minutes));
	else
		minutes_str = ft_itoa(minutes);
	if (seconds < 10)
		seconds_str = ft_strjoin("0", ft_itoa(seconds));
	else
		seconds_str = ft_itoa(seconds);
	if (hundredths < 10)
		hundredths_str = ft_strjoin("0", ft_itoa(hundredths));
	else
		hundredths_str = ft_itoa(hundredths);
	cub3d->timer.text_time = ft_strjoin(minutes_str, ":");
	cub3d->timer.text_time = ft_strjoin(cub3d->timer.text_time, seconds_str);
	cub3d->timer.text_time = ft_strjoin(cub3d->timer.text_time, ".");
	cub3d->timer.text_time = ft_strjoin(cub3d->timer.text_time, hundredths_str);
	free(minutes_str);
	free(seconds_str);
	free(hundredths_str);
}

void	draw_timer(cub3d_t *cub3d)
{
	update_timer(cub3d);
	mlx_delete_image(cub3d->mlx, cub3d->timer.img_time);
	cub3d->timer.img_time = mlx_put_string(cub3d->mlx, cub3d->timer.text_time, cub3d->timer.pos.x, cub3d->timer.pos.y);
	cub3d->timer.img_time->instances[0].x -= cub3d->timer.img_time->width;
}

void	print_timer(cub3d_t *cub3d)
{
	printf("Time passed: %f\n", elapsed_time(cub3d));
}