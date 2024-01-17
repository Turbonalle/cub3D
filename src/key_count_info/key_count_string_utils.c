/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_count_string_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:03:27 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 18:06:33 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	nullify_strings(char **text1, char **text2, char **text3)
{
	*text1 = NULL;
	*text2 = NULL;
	*text3 = NULL;
}

void	free_non_null_strings(char *text1, char *text2, char *text3)
{
	if (text1)
		free(text1);
	if (text2)
		free(text2);
	if (text3)
		free(text3);
}
