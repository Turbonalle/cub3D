/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:52:22 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 16:26:03 by slampine         ###   ########.fr       */
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

int	err_number(char *error_message, int num)
{
	write(2, TERMINAL_RED, ft_strlen(TERMINAL_RED));
	write(2, "Error\n", 6);
	write(2, error_message, ft_strlen(error_message));
	ft_putnbr_fd(num, 2);
	write(2, TERMINAL_RESET, ft_strlen(TERMINAL_RESET));
	write(2, "\n", 1);
	return (FAIL);
}
