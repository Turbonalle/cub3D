/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_colors.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:35:34 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:35:36 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_COLORS_H
# define TERMINAL_COLORS_H

# define TERMINAL_RESET "\001\e[0m\002"
# define TERMINAL_BLACK "\001\e[30m\002"
# define TERMINAL_RED "\001\e[31m\002"
# define TERMINAL_GREEN "\001\e[32m\002"
# define TERMINAL_YELLOW "\001\e[33m\002"
# define TERMINAL_BLUE "\001\e[34m\002"
# define TERMINAL_PURPLE "\001\e[35m\002"
# define TERMINAL_CYAN "\001\e[36m\002"
# define TERMINAL_WHITE "\001\e[37m\002"
# define TERMINAL_DEFAULT "\001\e[39m\002"

# define TERMINAL_BLACK_BOLD "\001\e[1;30m\002"
# define TERMINAL_RED_BOLD "\001\e[1;31m\002"
# define TERMINAL_GREEN_BOLD "\001\e[1;32m\002"
# define TERMINAL_YELLOW_BOLD "\001\e[1;33m\002"
# define TERMINAL_BLUE_BOLD "\001\e[1;34m\002"
# define TERMINAL_PURPLE_BOLD "\001\e[1;35m\002"
# define TERMINAL_CYAN_BOLD "\001\e[1;36m\002"
# define TERMINAL_WHITE_BOLD "\001\e[1;37m\002"
# define TERMINAL_DEFAULT_BOLD "\001\e[1;39m\002"

# define TERMINAL_BG_BLACK "\001\e[40m\002"
# define TERMINAL_BG_RED "\001\e[41m\002"
# define TERMINAL_BG_GREEN "\001\e[42m\002"
# define TERMINAL_BG_YELLOW "\001\e[43m\002"
# define TERMINAL_BG_BLUE "\001\e[44m\002"
# define TERMINAL_BG_PURPLE "\001\e[45m\002"
# define TERMINAL_BG_CYAN "\001\e[46m\002"
# define TERMINAL_BG_WHITE "\001\e[47m\002"
# define TERMINAL_BG_DEFAULT "\001\e[49m\002"

# define TERMINAL_BG_BLACK_BOLD "\001\e[1;40m\002"
# define TERMINAL_BG_RED_BOLD "\001\e[1;41m\002"
# define TERMINAL_BG_GREEN_BOLD "\001\e[1;42m\002"
# define TERMINAL_BG_YELLOW_BOLD "\001\e[1;43m\002"
# define TERMINAL_BG_BLUE_BOLD "\001\e[1;44m\002"
# define TERMINAL_BG_PURPLE_BOLD "\001\e[1;45m\002"
# define TERMINAL_BG_CYAN_BOLD "\001\e[1;46m\002"
# define TERMINAL_BG_WHITE_BOLD "\001\e[1;47m\002"
# define TERMINAL_BG_DEFAULT_BOLD "\001\e[1;49m\002"

#endif