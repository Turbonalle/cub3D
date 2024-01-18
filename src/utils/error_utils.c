/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:52:22 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 10:58:35 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	err(char *error_message)
{
	write(2, TERMINAL_RED, ft_strlen(TERMINAL_RED));
	write(2, "Error\n", 6);
	write(2, error_message, ft_strlen(error_message));
	write(2, TERMINAL_RESET, ft_strlen(TERMINAL_RESET));
	write(2, "\n", 1);
	return (FAIL);
}
