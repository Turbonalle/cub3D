/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_health.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:09:42 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/19 11:25:25 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	set_health(t_cub3d *cub3d)
{
	if (get_current_level(cub3d) == 9)
		cub3d->player.health = 3;
	else
		cub3d->player.health = 1;
}
