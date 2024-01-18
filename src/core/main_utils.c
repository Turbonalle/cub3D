/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:04:25 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:09:56 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	free_already_allocated(t_cub3d *cub3d, int i)
{
	while (i > 0)
	{
		free_list(cub3d->levels[--i].map_list);
		if (i >= 0)
			free_backup(cub3d->levels[i]);
	}
	free(cub3d->levels);
}

char	*create_path(int i)
{
	char	*level_i;
	char	*path;
	char	*full_path;

	level_i = ft_itoa(i);
	if (!level_i)
		return (NULL);
	path = ft_strjoin(LEVEL_PREFIX, level_i);
	if (!path)
		return (free(level_i), NULL);
	full_path = ft_strjoin(path, ".cub");
	if (!full_path)
		return (free(level_i), free(path), NULL);
	free(level_i);
	free(path);
	return (full_path);
}

int	read_all_levels(t_cub3d *cub3d)
{
	int		fd;
	int		i;
	char	*full_path;

	i = 1;
	while (i < LEVELS + 1)
	{
		full_path = create_path(i);
		if (full_path == NULL)
			return (free_already_allocated(cub3d, i), err("Malloc error"));
		fd = open(full_path, O_RDONLY);
		if (fd < 0)
			return (free(full_path), free_already_allocated(cub3d, i),
				err("Failed to open level file"));
		if (!read_cub_file(&cub3d->levels[i], full_path))
			return (free(full_path), free_already_allocated(cub3d, i),
				err("Failed to read level file"));
		close(fd);
		free(full_path);
		i++;
	}
	return (1);
}

static void	write_down(t_record *ptr, int fd)
{
	t_record	*next;
	char		*time;

	while (ptr)
	{
		if (ptr->time > 0)
		{
			time = ft_itoa(ptr->time);
			write(fd, time, ft_strlen(time));
			write(fd, " ", 1);
			write(fd, ptr->name, ft_strlen(ptr->name));
			write(fd, "\n", 1);
			free(time);
		}
		next = ptr->next;
		free(ptr->name);
		free(ptr);
		ptr = next;
	}
}

int	write_records(t_cub3d *cub3d, t_level *levels)
{
	int			fd;
	int			i;
	t_record	*ptr;

	fd = open(RECORD_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (!err("Failed to open records file"));
	i = 0;
	while (++i < cub3d->n_levels + 1)
	{
		ptr = levels[i].records;
		if (ptr)
			write_down(ptr, fd);
		write(fd, "\n", 1);
	}
	close(fd);
	return (SUCCESS);
}
