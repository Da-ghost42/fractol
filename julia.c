/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:42:50 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/22 12:50:03 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

void	init_julia(t_fractal *fractal)
{
		fractal->mlx = mlx_init();
		fractal->win = mlx_new_window(fractal->mlx,SIZE,SIZE,"FRACT-OL");
		fractal->img = mlx_new_image(fractal->mlx,SIZE,SIZE);
		fractal->addr = mlx_get_data_addr(fractal->img,&fractal->bpp,&fractal->line_length,&fractal->endian);
		fractal->zoom = 0.5;
		fractal->min_x = -2;
		fractal->max_x = 2;
		fractal->min_y = -2.0;
		fractal->max_y = 2.0;
		fractal->c.r = -1;
		fractal->c.i = 0;
		fractal->iter = 150;
		fractal->ju = which_julia(fractal);
		draw_julia(fractal);
}

int iterate_julia(int x,int y,t_fractal *fractal)
{
    int i;
	double tmp;
    t_complex z;

    i = 0;
	z.r = fractal->min_x + x * (fractal->max_x - fractal->min_x) / SIZE;
	z.i = fractal->min_y + y * (fractal->max_y - fractal->min_y) / SIZE;
    while (z.r * z.r + z.i * z.i < 4 && i < fractal->iter)
    {
        tmp = z.r * z.r - z.i * z.i + fractal->ju.r;
        z.i = 2 * z.r * z.i+ fractal->ju.i;
        z.r = tmp;
        i++;
    }
    return i;
}

void	draw_julia(t_fractal *fractal)
{
	int x;
	int y;
	int i;

	x = -1;
	while (++x < SIZE)
	{
		y = -1;
		while (++y < SIZE)
		{
			i = iterate_julia(x,y,fractal);
			if (i == fractal->iter)
				set_pix_color(fractal,x,y,0x000000);
			else
				set_pix_color(fractal,x,y,get_color(i));
		}
	}
	mlx_put_image_to_window(fractal->mlx,fractal->win,fractal->img,0,0);
}