/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:52:22 by vvagapov          #+#    #+#             */
/*   Updated: 2023/11/15 11:04:06 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	err(char *error_message)
{
	printf(TERMINAL_RED);
	printf("Error: %s\n", error_message);
	printf(TERMINAL_RESET);
	return (FAIL);
}
//------------------------------------------------------------------------------

void	empty_map_list(map_node_t *node)
{
	map_node_t	*temp;

	while (node)
	{
		temp = node->next;
		free(node->line);
		free(node);
		node = temp;
	}
}
