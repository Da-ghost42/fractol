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

// int zoom_in(int x, int y, t_fractal *fractal)
// {
//     fractal->zoom *= ZF;
//     fractal->min_x += (x - WIDTH / 2) * ((fractal->max_x - fractal->min_x)/ WIDTH) * (1 / ZF);
//     fractal->max_x = fractal->min_x + (fractal->max_x - fractal->min_x) / ZF;
//     // fractal->min_y += (y - HEIGHT / 2) * ((fractal->max_y - fractal->min_y) / HEIGHT) * (1 / ZF);
//     // fractal->max_y = fractal->min_y + (fractal->max_y - fractal->min_y) / ZF;
// 	fractal->min_y += (y - HEIGHT / 2) * ((fractal->max_y - fractal->min_y) / HEIGHT) * (1 / ZF);
// 	fractal->max_y = fractal->min_y + (fractal->max_y - fractal->min_y) / ZF;
//     draw_fractal(fractal);
//     return 0;
// }

// int zoom_out(int x, int y, t_fractal *fractal)
// {
//     fractal->zoom /= ZF;
//     fractal->min_x -= (x - WIDTH / 2) * ((fractal->max_x - fractal->min_x)/ WIDTH) * (1 / ZF);
//     fractal->max_x = fractal->min_x + (fractal->max_x - fractal->min_x) / ZF;
//     fractal->min_y -= (y - HEIGHT / 2) * ((fractal->max_y - fractal->min_y) / HEIGHT) * (1 / ZF);
//     fractal->max_y = fractal->min_y + (fractal->max_y - fractal->min_y) / ZF;

//     draw_fractal(fractal);
//     return 0;
// }
int zoom_out(int x, int y, t_fractal *fractal)
{
	double j;
	double i;

	j = (fractal->max_x - fractal->min_x) / ZF;
	i = (fractal->max_y - fractal->min_y) / ZF;
    fractal->min_x = fractal->min_x + (x - WIDTH / 2) * j / WIDTH;
    fractal->max_x = fractal->min_x + j;
    fractal->min_y = fractal->min_y + (y - HEIGHT / 2) * i / HEIGHT;
    fractal->max_y = fractal->min_y +i;

    draw_fractal(fractal);
    return 0;
}

int zoom_in(int x, int y, t_fractal *fractal)
{
	double j;
	double i;

	j = (fractal->max_x - fractal->min_x) * ZF;
	i = (fractal->max_y - fractal->min_y) * ZF;
    fractal->min_x = fractal->min_x - (x - WIDTH / 2) * j * ZF / WIDTH;
    fractal->max_x = fractal->min_x + j;
    fractal->min_y = fractal->min_y - (y - HEIGHT / 2) * i / HEIGHT;
    fractal->max_y = fractal->min_y + i;

    draw_fractal(fractal);
    return 0;
}

int	mouse_set(int keycode,int x,int y,t_fractal *fractal)
{
	if (keycode == MOUSE_UP)
		zoom_in(x,y,fractal);
	if (keycode == MOUSE_DW)
		zoom_out(x,y,fractal);
	return (0);
}

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
		fractal->zoom = 1.5;
		fractal->move_x = 0.0;
		fractal->move_y = 0.0;
		fractal->min_x = -2.5;
		fractal->max_x = 1;
		fractal->min_y = -2.0;
		fractal->max_y = 2.0;
		draw_fractal(fractal);
}

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
			// c.r = fractal->min_x + (x - WIDTH / 2 + fractal->move_x) * (fractal->max_x - fractal->min_x) / (WIDTH * fractal->zoom);
			// c.i = fractal->min_y + (y - HEIGHT / 2 + fractal->move_y) * (fractal->max_y - fractal->min_y) / (HEIGHT * fractal->zoom);

			c.r = fractal->min_x + x * (fractal->max_x - fractal->min_x) / WIDTH;
			c.i = fractal->min_y + y * (fractal->max_y - fractal->min_y) / HEIGHT;
			i = mandel_iteration(c);
			if (i == MAX_ITER)
				set_pix_color(fractal,x,y,0x2874A6);
			else
				set_pix_color(fractal,x,y,0x000000 + i * 0x001111);
		}
	}
		mlx_put_image_to_window(fractal->mlx,fractal->win,fractal->img,0,0);
}

void	hooks(t_fractal *fractal)
{
	mlx_hook(fractal->win,2,0,keypress_set,fractal->mlx);
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
		ft_putstr_fd("after mandel",2);
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