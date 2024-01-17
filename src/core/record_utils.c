/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:19:44 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 20:09:40 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	get_record_time(char *line, int *time)
{
	char	*ptr;

	ptr = line;
	*time = 0;
	while (*ptr && ft_isdigit(*ptr))
	{
		*time = *time * 10 + (*ptr - '0');
		ptr++;
	}
	if (*ptr != ' ')
		return (FAIL);
	return (SUCCESS);
}

int	get_record_name(char *line, char **name)
{
	char	*name_start;
	int		i;

	name_start = ft_strchr(line, ' ');
	if (!name_start)
		return (FAIL);
	name_start++;
	i = 0;
	while (name_start[i] && name_start[i] != '\n')
	{
		if (!ft_isalpha(name_start[i]))
			return (FAIL);
		i++;
	}
	if (i == 0 || i > MAX_NAME_LENGTH
		|| (name_start[i] != '\n' && name_start[i] != '\0'))
		return (FAIL);
	*name = ft_substr(line, name_start - line, i);
	if (!*name)
		return (FAIL);
	return (SUCCESS);
}

record_t	*new_record(int time, char *name)
{
	record_t	*new;

	new = malloc(sizeof(record_t));
	if (!new)
		return (NULL);
	new->time = time;
	new->name = name;
	create_time_string(new->time_str, time);
	new->text_name = NULL;
	new->text_time = NULL;
	new->next = NULL;
	return (new);
}

int	count_records(record_t *records)
{
	int			count;
	record_t	*ptr;

	count = 0;
	ptr = records;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

void	create_time_string(char *time_str, int time)
{
	if (time <= 0 || time >= 6000000)
	{
		time_str[0] = '0';
		time_str[1] = '0';
		time_str[2] = ':';
		time_str[3] = '0';
		time_str[4] = '0';
		time_str[5] = '.';
		time_str[6] = '0';
		time_str[7] = '0';
	}
	else
	{
		time_str[0] = '0' + time / 600000;
		time_str[1] = '0' + time / 60000 % 10;
		time_str[2] = ':';
		time_str[3] = '0' + time / 10000 % 6;
		time_str[4] = '0' + time / 1000 % 10;
		time_str[5] = '.';
		time_str[6] = '0' + time / 100 % 10;
		time_str[7] = '0' + time / 10 % 10;
	}
	time_str[8] = '\0';
}
