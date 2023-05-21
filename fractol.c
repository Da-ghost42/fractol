// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   fractol.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/11 02:18:11 by mboutuil          #+#    #+#             */
// /*   Updated: 2023/05/19 20:53:52 by mboutuil         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include"fractol.h"


void	init_julia(t_fractal *fractal)
{
		fractal->mlx = mlx_init();
		fractal->win = mlx_new_window(fractal->mlx,WIDTH,HEIGHT,"FRACT-OL");
		fractal->img = mlx_new_image(fractal->mlx,WIDTH,HEIGHT);
		fractal->addr = mlx_get_data_addr(fractal->img,&fractal->bpp,&fractal->line_length,&fractal->endian);
		fractal->zoom = 0.5;
		fractal->ju.r = -0.8;
		fractal->ju.i = 0.156;
		fractal->min_x = -2;
		fractal->max_x = 2;
		fractal->min_y = -2.0;
		fractal->max_y = 2.0;
		fractal->type = JULIA;
		draw_fractal(fractal);
}

void	hooks(t_fractal *fractal)
{
	mlx_hook(fractal->win,17,0,keypress_set,fractal);
	mlx_hook(fractal->win,2,1L,key_set,fractal);
	mlx_hook(fractal->win, 5, 0, mouse_set, fractal);
	mlx_hook(fractal->win, 4, 0,mouse_set, fractal);
}

void	init_fractol(t_fractal *fractal,int set)
{
	if (set == MANDELBROT)
	{
		fractal = (t_fractal *)malloc(sizeof(t_fractal));
		if (!fractal)
			exit (EXIT_FAILURE);
		init_mandel(fractal);
	}
	if (set == JULIA)
	{
		fractal = (t_fractal *)malloc(sizeof(t_fractal));
		if (!fractal)
			exit (EXIT_FAILURE);
		init_julia(fractal);
	}
	hooks(fractal);
	mlx_loop(fractal->mlx);
}

int	check_args(char *av)
{
	if (ft_strncmp(av,"Mandelbrot",ft_strlen(av)) == 0)
		return(MANDELBROT);
	if (ft_strncmp(av,"Julia",ft_strlen(av)) == 0)
		return (JULIA);
	else
	{
		ft_putstr_fd("Invalid arguments\n",2);
		exit (EXIT_FAILURE);
	}
}


int main (int ac ,char **av)
{
	t_fractal *fractal;
	// int	i;

	fractal = NULL;
	if (ac != 2)
	{
		ft_putstr_fd("invalid arguments\n",2);
		exit(EXIT_FAILURE);
	}
	init_fractol(fractal,check_args(av[1]));
	// mlx_loop(fractal->mlx);
}