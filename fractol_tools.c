/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:46:23 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/23 16:42:18 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

void	set_pix_color(t_fractal *fractal, int x, int y, int color)
{
	char	*dst;

	dst = fractal->addr + (y * fractal->line_length + x * (fractal->bpp / 8));
	*(unsigned int *)dst = color;
}

int	zoom_out(int x, int y, t_fractal *fractal)
{
	double	j;
	double	i;

	i = fractal->min_x + x * (fractal->max_x - fractal->min_x) / SIZE;
	j = fractal->min_y + y * (fractal->max_y - fractal->min_y) / SIZE;
	fractal->min_x /= fractal->zoom;
	fractal->max_x /= fractal->zoom;
	fractal->min_y /= fractal->zoom;
	fractal->max_y /= fractal->zoom;
	fractal->min_x -= i;
	fractal->max_x -= i;
	fractal->min_y -= j;
	fractal->max_y -= j;
	if (fractal->iter > 10)
		fractal->iter -= 10;
	draw_fractal (fractal);
	return (0);
}

int	zoom_in(int x, int y, t_fractal *fractal)
{
	double	j;
	double	i;

	i = fractal->min_x + x * (fractal->max_x - fractal->min_x) / SIZE;
	j = fractal->min_y + y * (fractal->max_y - fractal->min_y) / SIZE;
	fractal->min_x += i;
	fractal->max_x += i;
	fractal->min_y += j;
	fractal->max_y += j;
	fractal->min_x *= fractal->zoom;
	fractal->max_x *= fractal->zoom;
	fractal->min_y *= fractal->zoom;
	fractal->max_y *= fractal->zoom;
	fractal->iter += 10;
	draw_fractal (fractal);
	return (0);
}

int	get_color(t_fractal *fractal, int i)
{
	int	r;
	int	g;
	int	b;

	r = (i + 60) % 256;
	b = (i + 180) % 256;
	g = (i + 100) % 256 + fractal->i;
	return (r << 16 | g << 8 | b);
}

int	animate(int x, int y, t_fractal *fractal)
{
	if (fractal->lock == 1 && fractal->type != MANDELBROT
		&& fractal->type != BURN)
	{
		fractal->ju.i = fractal->min_x + x
			* (fractal->max_x - fractal->min_x) / SIZE;
		fractal->ju.r = fractal->min_y + y
			* (fractal->max_y - fractal->min_y) / SIZE;
		draw_julia(fractal);
	}
	if (fractal->lock == -1 && fractal->type != MANDELBROT
		&& fractal->type != BURN)
		draw_julia(fractal);
	return (0);
}
