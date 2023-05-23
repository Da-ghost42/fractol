/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:26:00 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/23 16:15:59 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

void	hooks(t_fractal *fractal)
{
	mlx_hook (fractal->win, 6, 0, animate, fractal);
	mlx_hook (fractal->win, 17, 0, keypress_set, fractal);
	mlx_hook (fractal->win, 2, 1L, key_set, fractal);
	mlx_hook (fractal->win, 1, 0, mouse_set, fractal);
	mlx_hook (fractal->win, 5, 0, mouse_set, fractal);
	mlx_hook (fractal->win, 4, 0, mouse_set, fractal);
}

int	mouse_set(int keycode, int x, int y, t_fractal *fractal)
{
	if (keycode == MOUSE_DW)
		zoom_in(x, y, fractal);
	if (keycode == MOUSE_UP)
		zoom_out(x, y, fractal);
	return (0);
}

int	keypress_set(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx, fractal->win);
	free (fractal);
	exit (0);
	return (0);
}

int	key_set(int keycode, t_fractal *fractal)
{
	if (keycode == KEY_ESC)
	{	
		mlx_destroy_window (fractal->mlx, fractal->win);
		free (fractal);
		exit (0);
	}
	if (keycode == 49)
		fractal->lock *= -1;
	if (keycode == ARR_L || keycode == ARR_R || keycode == ARR_D
		|| keycode == ARR_U)
		arrows(keycode, fractal);
	if (keycode == 257)
	{
		fractal->i += 10;
		mlx_clear_window(fractal->mlx, fractal->win);
		draw_fractal(fractal);
	}
	return (0);
}

int	arrows(int keycode, t_fractal *fractal)
{
	if (keycode == ARR_L)
	{
		fractal->min_x += 0.1;
		fractal->max_x += 0.1;
	}
	else if (keycode == ARR_R)
	{
		fractal->min_x -= 0.1;
		fractal->max_x -= 0.1;
	}
	else if (keycode == ARR_U)
	{
		fractal->min_y += 0.1;
		fractal->max_y += 0.1;
	}
	else if (keycode == ARR_D)
	{
		fractal->min_y -= 0.1;
		fractal->max_y -= 0.1;
	}
	mlx_clear_window (fractal->mlx, fractal->win);
	draw_fractal (fractal);
	return (0);
}
