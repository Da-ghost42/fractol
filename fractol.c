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

void	draw_fractal(t_fractal *fractal)
{
	if (fractal->type == MANDELBROT)
		draw_mandel(fractal);
	if (fractal->type == JULIA)
		draw_julia(fractal);
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