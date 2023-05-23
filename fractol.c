/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:18:11 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/23 15:54:10 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

void	draw_fractal(t_fractal *fractal)
{
	if (fractal->type == MANDELBROT)
		draw_mandel(fractal);
	if (fractal->type == JULIA || fractal->type == JULIA_1
		|| fractal->type == JULIA_2)
		draw_julia(fractal);
	if (fractal->type == BURN)
		draw_burn(fractal);
}

void	init_fractol(t_fractal *fractal, int set)
{
	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (!fractal)
		exit (EXIT_FAILURE);
	if (set == MANDELBROT)
		init_mandel (fractal);
	if (set == JULIA)
	{
		fractal->type = JULIA;
		init_julia (fractal);
	}
	if (set == JULIA_1)
	{
		fractal->type = JULIA_1;
		init_julia (fractal);
	}
	if (set == JULIA_2)
	{
		fractal->type = JULIA_2;
		init_julia (fractal);
	}
	if (set == BURN)
		init_burn (fractal);
	hooks (fractal);
	mlx_loop (fractal->mlx);
}

t_complex	which_julia(t_fractal *fractal)
{
	t_complex	c;

	c.r = 0;
	c.i = 0;
	if (fractal->type == JULIA)
	{
		c.r = 0;
		c.i = -0.8;
	}
	else if (fractal->type == JULIA_1)
	{
		c.r = -0.8;
		c.i = -0.156;
	}
	else if (fractal->type == JULIA_2)
	{
		c.r = -0.835;
		c.i = -0.2321;
	}
	return (c);
}

int	check_args(char *av)
{
	if (ft_strncmp(av, "Mandelbrot", ft_strlen(av)) == 0)
		return (MANDELBROT);
	if (ft_strncmp(av, "Julia", ft_strlen(av)) == 0)
		return (JULIA);
	if (ft_strncmp(av, "Julia1", ft_strlen(av)) == 0)
		return (JULIA_1);
	if (ft_strncmp(av, "Julia2", ft_strlen(av)) == 0)
		return (JULIA_2);
	if (ft_strncmp(av, "burningship", ft_strlen(av)) == 0)
		return (BURN);
	else
	{
		ft_putstr_fd ("Invalid arguments\n", 2);
		exit (EXIT_FAILURE);
	}
}

int	main(int ac, char **av)
{
	t_fractal	*fractal;

	fractal = NULL;
	if (ac != 2)
	{
		ft_putstr_fd ("invalid arguments\n", 2);
		exit (EXIT_FAILURE);
	}
	init_fractol (fractal, check_args(av[1]));
}
