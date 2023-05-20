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

int	keypress_set(int keycode,t_fractal *fractal)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(fractal->mlx,fractal->win);
		exit (0);
	}
	return (0);
}

void	set_pix_color(t_fractal *fractal,int x,int y,int color)
{
	char	*dst;

	dst = fractal->addr + (y * fractal->line_length + x * (fractal->bpp / 8));
	*(unsigned int*)dst = color;
}

void	init_mandel(t_fractal *fractal)
{
		fractal->mlx = mlx_init();
		fractal->win = mlx_new_window(fractal->mlx,WIDTH,HEIGHT,"FRACT-OL");
		fractal->img = mlx_new_image(fractal->mlx,WIDTH,HEIGHT);
		fractal->addr = mlx_get_data_addr(fractal->img,&fractal->bpp,&fractal->line_length,&fractal->endian);
		fractal->zoom = 1.1;
		fractal->move_x = -0.5;
		fractal->move_y = 0.0;
		fractal->min_x = -2;
		fractal->max_x = 2;
		fractal->min_y = -2;
		fractal->max_y = 2;
		draw_fractal(fractal);
}
// int	mandel_iteration(t_complex c)
// {
// 	int			i;
// 	t_complex	tmp;
// 	t_complex	z = {0,0};

// 	i = 0;
// 	while (z.r * z.r + z.i * z.i < 4 && i < MAX_ITER)
// 	{
// 		z.r = z.r * z.r - z.i * z.i + c.r;
// 		z.i = 2 * z.r * z.i + c.i;
// 		tmp = z;
// 		i++;
// 	}
// 	return i;
// }
int mandel_iteration(t_complex c)
{
	int i;
	t_complex tmp;
	t_complex z;

	i = 0;
	z.r = 0;
	z.i = 0;
	while (z.r * z.r + z.i * z.i < 4 && i < MAX_ITER)
	{
		tmp.r = z.r * z.r - z.i * z.i + c.r;
		tmp.i = 2 * z.r * z.i + c.i;
		z = tmp;
		i++;
	}
	return i;
}
void	draw_fractal(t_fractal *fractal)
{
	int	x;
	int	y;
	int	i;
	t_complex c;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			// c.r = (x - WIDTH / 2) * fractal->zoom / WIDTH + fractal->move_x; 
			// c.i = (x - HEIGHT / 2) * fractal->zoom / HEIGHT + fractal->move_y;
			c.r = fractal->min_x + x * (fractal->max_x - fractal->min_x) / WIDTH;
			c.i = fractal->min_y + y * (fractal->max_y - fractal->min_y) / HEIGHT;
			i = mandel_iteration(c);
			if (i == MAX_ITER)
				set_pix_color(fractal,x,y,0x2874A6);
			else
				set_pix_color(fractal,x,y,0xFFFFFF * i / 100);
		}
	}
		mlx_put_image_to_window(fractal->mlx,fractal->win,fractal->img,0,0);
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
		ft_putstr_fd("after mandel",2);
	}
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

void	hooks(t_fractal *fractal)
{
	mlx_hook(fractal->win,2,0,keypress_set,fractal->mlx);
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
	hooks(fractal);
	// mlx_loop(fractal->mlx);
}