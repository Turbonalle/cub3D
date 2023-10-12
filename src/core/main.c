/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:09:19 by vvagapov          #+#    #+#             */
/*   Updated: 2023/10/12 13:31:41 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int main(int ac, char **av)
{
	cub3d_t	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	if (!read_cub_file(&cub3d, av[1]) || !init_cub3d(&cub3d))
		return (1);
	print_info(&cub3d); // DEBUG
	start_game(&cub3d);
	free_cub3d(&cub3d);
	return (0);
}
