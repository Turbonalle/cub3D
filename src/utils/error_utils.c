/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:52:22 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/10 14:09:28 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	err(char *error_message)
{
	// TODO: potentially set game state to CRASH
	printf(TERMINAL_RED);
	printf("Error:\n%s\n", error_message);
	printf(TERMINAL_RESET);
	return (FAIL);
}
