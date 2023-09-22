/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:43:01 by jbagger           #+#    #+#             */
/*   Updated: 2023/04/18 11:46:37 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_copy_and_free(char *buffer, char *add_to_end)
{
	char	*temp;

	temp = ft_strjoin(buffer, add_to_end);
	free(buffer);
	return (temp);
}

static char	*ft_get_rest(char *buffer)
{
	char	*trimmed;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		i++;
	}
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	trimmed = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!trimmed)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		trimmed[j++] = buffer[i++];
	free(buffer);
	return (trimmed);
}

static char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	line[i + 1] = '\0';
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*ft_read(char *result, int fd)
{
	char	*buffer;
	int		bytes_read;

	if (!result)
		result = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		result = ft_copy_and_free(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	buffer = ft_read(buffer, fd);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_get_rest(buffer);
	return (line);
}