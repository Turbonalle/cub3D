/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:58:00 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 13:59:15 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

char	*create_minutes_str(cub3d_t *cub3d)
{
	int		minutes;
	char	*minutes_str;
	char	*temp;

	cub3d->run_time = elapsed_time(cub3d);
	minutes = (int)cub3d->run_time / 60;
	if (minutes < 10)
	{
		temp = ft_itoa(minutes);
		if (!temp)
			return (NULL);
		minutes_str = ft_strjoin("0", temp);
		free(temp);
	}
	else
		minutes_str = ft_itoa(minutes);
	return (minutes_str);
}

char	*create_seconds_str(cub3d_t *cub3d)
{
	int		seconds;
	char	*seconds_str;
	char	*temp;

	cub3d->run_time = elapsed_time(cub3d);
	seconds = (int)cub3d->run_time % 60;
	if (seconds < 10)
	{
		temp = ft_itoa(seconds);
		if (!temp)
			return (NULL);
		seconds_str = ft_strjoin("0", temp);
		free(temp);
	}
	else
		seconds_str = ft_itoa(seconds);
	return (seconds_str);
}

char	*create_hundredths_str(cub3d_t *cub3d)
{
	int		hundredths;
	char	*hundredths_str;
	char	*temp;

	hundredths = (int)(cub3d->run_time * 100) % 100;
	if (hundredths < 10)
	{
		temp = ft_itoa(hundredths);
		if (!temp)
			return (NULL);
		hundredths_str = ft_strjoin("0", temp);
		free(temp);
	}
	else
		hundredths_str = ft_itoa(hundredths);
	return (hundredths_str);
}

void	create_timer_text(cub3d_t *cub3d, char *minutes_str,
	char *seconds_str, char *hundredths_str)
{
	char	*temp;

	temp = ft_strjoin(minutes_str, ":");
	if (!temp)
		return (free_three_strs(minutes_str, seconds_str, hundredths_str));
	cub3d->timer.text_time = ft_strjoin(temp, seconds_str);
	free(temp);
	if (!cub3d->timer.text_time)
		return (free_three_strs(minutes_str, seconds_str, hundredths_str));
	temp = ft_strjoin(cub3d->timer.text_time, ".");
	free(cub3d->timer.text_time);
	if (!temp)
		return (free_three_strs(minutes_str, seconds_str, hundredths_str));
	cub3d->timer.text_time = ft_strjoin(temp, hundredths_str);
	free(temp);
	free_three_strs(minutes_str, seconds_str, hundredths_str);
}

void	update_timer(cub3d_t *cub3d)
{
	char	*minutes_str;
	char	*seconds_str;
	char	*hundredths_str;

	cub3d->run_time = elapsed_time(cub3d);
	minutes_str = NULL;
	seconds_str = NULL;
	hundredths_str = NULL;
	minutes_str = create_minutes_str(cub3d);
	if (!minutes_str)
		return (free_three_strs(minutes_str, seconds_str, hundredths_str));
	seconds_str = create_seconds_str(cub3d);
	if (!seconds_str)
		return (free_three_strs(minutes_str, seconds_str, hundredths_str));
	hundredths_str = create_hundredths_str(cub3d);
	if (!hundredths_str)
		return (free_three_strs(minutes_str, seconds_str, hundredths_str));
	create_timer_text(cub3d, minutes_str, seconds_str, hundredths_str);
}
