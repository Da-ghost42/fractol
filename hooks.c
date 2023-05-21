/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:26:00 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/22 00:20:38 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

void	hooks(t_fractal *fractal)
{
	mlx_hook(fractal->win,17,0,keypress_set,fractal);
	mlx_hook(fractal->win,2,1L,key_set,fractal);
	mlx_hook(fractal->win, 5, 0, mouse_set, fractal);
	mlx_hook(fractal->win, 4, 0,mouse_set, fractal);
}

int	mouse_set(int keycode,int x,int y,t_fractal *fractal)
{
	if (keycode == MOUSE_DW)
		zoom_in(x,y,fractal);
	if (keycode == MOUSE_UP)
		zoom_out(x,y,fractal);
	return (0);
}

int	keypress_set(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx,fractal->win);
	free(fractal);
	exit (0);
	return (0);
}
int	key_set(int o ,t_fractal *fractal)
{
	if (o == 53)
	{	
	mlx_destroy_window(fractal->mlx,fractal->win);
	free(fractal);
	exit (0);
	}
	return (0);
}