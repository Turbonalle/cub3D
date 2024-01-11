/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:30:43 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 13:30:46 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	get_current_level(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (++i < cub3d->n_levels + 1)
	{
		if (cub3d->level == &cub3d->levels[i])
			return (i);
	}
	return (i);
}

int	all_alpha(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]))
			return (FAIL);
	}
	return (SUCCESS);
}

int	all_digits(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (FAIL);
	}
	return (SUCCESS);
}
