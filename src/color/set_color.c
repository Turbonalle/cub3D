/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:25:55 by slampine          #+#    #+#             */
/*   Updated: 2023/11/15 14:25:57 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	set_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	set_r(int rgba, int r)
{
	int	g;
	int	b;
	int	a;

	g = get_g(rgba);
	b = get_b(rgba);
	a = get_a(rgba);
	return (set_rgba(r, g, b, a));
}

int	set_g(int rgba, int g)
{
	int	r;
	int	b;
	int	a;

	r = get_r(rgba);
	b = get_b(rgba);
	a = get_a(rgba);
	return (set_rgba(r, g, b, a));
}

int	set_b(int rgba, int b)
{
	int	r;
	int	g;
	int	a;

	r = get_r(rgba);
	g = get_g(rgba);
	a = get_a(rgba);
	return (set_rgba(r, g, b, a));
}

int	set_a(int rgba, int a)
{
	int	r;
	int	g;
	int	b;

	r = get_r(rgba);
	g = get_g(rgba);
	b = get_b(rgba);
	return (set_rgba(r, g, b, a));
}
