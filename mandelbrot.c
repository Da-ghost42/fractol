/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:24:17 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/23 16:14:23 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"
#include<math.h>

void	init_mandel(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	fractal->win = mlx_new_window(fractal->mlx, SIZE, SIZE, "FRACT-OL");
	fractal->img = mlx_new_image(fractal->mlx, SIZE, SIZE);
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bpp,
			&fractal->line_length, &fractal->endian);
	fractal->zoom = 0.5;
	fractal->min_x = -2;
	fractal->max_x = 2;
	fractal->min_y = -2.0;
	fractal->max_y = 2.0;
	fractal->iter = 150;
	fractal->i = 50;
	fractal->type = MANDELBROT;
	draw_fractal (fractal);
}

int	iteration(t_complex c, t_fractal *fractal)
{
	int			i;
	t_complex	tmp;
	t_complex	z;

	i = 0;
	z.i = 0;
	z.r = 0;
	while (z.r * z.r + z.i * z.i < 4 && i < fractal->iter)
	{
		tmp.r = z.r * z.r - z.i * z.i + c.r;
		tmp.i = 2 * z.r * z.i + c.i;
		z = tmp;
		i++;
	}
	return (i);
}

void	draw_mandel(t_fractal *fractal)
{
	int			i;
	int			x;
	int			y;
	t_complex	c;

	y = -1;
	while (++y < SIZE)
	{
		x = -1;
		while (++x < SIZE)
		{
			c.r = fractal->min_x + x
				* (fractal->max_x - fractal->min_x) / SIZE;
			c.i = fractal->min_y + y
				* (fractal->max_y - fractal->min_y) / SIZE;
			i = iteration(c, fractal);
			if (i == fractal->iter)
				set_pix_color(fractal, x, y, 0x000000);
			else
				set_pix_color(fractal, x, y, get_color(fractal, i));
		}
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}
