/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:18:11 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/18 10:23:06 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

// int handle_keypress(int keycode, t_fractal *fractal)
// {
// 	if (keycode == KEY_ESC)
// 	{
// 		mlx_destroy_window(fractal->mlx, fractal->win);
// 		exit(0);
// 	}
// 	return 0;
// }

t_sample get_color(int i)
{
    t_sample color;
    if (i == MAX_ITER)
	{
		color.r = 0x28;
		color.g = 0x74;
		color.b = 0xA6;
	}
    else
    {
        color.r = (0xFF * i) / MAX_ITER;
        color.g = (0xFF * i) / MAX_ITER;
        color.b = (0xFF * i) / MAX_ITER;
    }
    return color;
}

void set_pixel_color(t_fractal *fractal, int x, int y, t_sample color)
{
	int	pixel_color;

	color.r /= SAMPLE;
	color.g /= SAMPLE;
	color.b /= SAMPLE;
	pixel_color = (color.r << 16) | color.g << 8 | color.b;
	char *dst = fractal->addr + (y * fractal->line_length + x * (fractal->bpp / 8));
	*(unsigned int*)dst = pixel_color;
}

void set_fractal_type(t_fractal *fractal, char **argv)
{
	if (ft_strncmp(argv[1], "Mandelbrot", ft_strlen(argv[1])) == 0)
		fractal->type = MANDELBROT;
	else if (ft_strncmp(argv[1], "Julia", ft_strlen(argv[1])) == 0)
		fractal->type = JULIA;
	else
	{
		ft_putstr_fd("Invalid fractal type\n", 2);
		exit(EXIT_FAILURE);
	}
}

int perform_iteration(t_complex c)
{
	int i = 0;
	t_complex tmp;
	t_complex z ={0 , 0};
	while (z.r * z.r + z.i * z.i < 4 && i < MAX_ITER)
	{
		z.r = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * z.r * z.i + c.i; 
		tmp = z;
		i++;
	}
	return i;
}

void draw_fractal(t_fractal *fractal)
{
	int	x;
	int	y;
	int	i;
	int	j;
	t_complex c;
	t_complex sample;
	t_sample	color;
	t_sample	color_pix;

	y = -1;
	while (++y < WIDTH)
	{
		x = -1;
		while (++x < HEIGHT)
		{
			i = 0;
			color.r = 0;
			color.g = 0;
			color.b = 0;
			while (i++ < SAMPLE)
			{
				sample.r = (x + i % 2) / WIDTH;
				sample.i = (y + i / 2) /HEIGHT;
				c.r = fractal->min_x + sample.r * (fractal->max_x - fractal->min_x);
				c.i = fractal->min_y + sample.i * (fractal->max_y - fractal->min_y);

				j = perform_iteration(c);
				color_pix = get_color(j);

				color.r += color_pix.r;
				color.g += color_pix.g;
				color.b += color_pix.b;

				set_pixel_color(fractal,x,y,color);
			}
		}
	}
		mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}


void init_fractal(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "FRACT-OL");
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bpp, &fractal->line_length, &fractal->endian);
	fractal->zoom = 1.1;
	fractal->move_x = -0.5;
	fractal->move_y = 0.0;
	fractal->gui = NULL;
}

int main (int ac,char **av)
{
	t_fractal *fractal;

	if (ac != 2)
	{
		write(2,"bad arguments",14);
		exit (1);
	}
	if (ft_strncmp(av[1],"Mandelbrot",ft_strlen(av[1])) != 0 && ft_strncmp(av[1],"Julia",ft_strlen(av[1])) != 0)
	{
		ft_putstr_fd("Invalid fractal type\n", 2);
		exit(EXIT_FAILURE);
	}

	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (!fractal)
		return 0;
	set_fractal_type(fractal,av);
	init_fractal(fractal);
	draw_fractal(fractal);
	// mlx_hook(fractal->win,48,0,handle_keypress,fractal->mlx);
	// mlx_hook(fractal->win,2,0,handle_keypress,fractal->mlx);
	// mlx_hook(fractal->win,4,0,handle_keypress,fractal->mlx);
	// mlx_hook(fractal->win,-1,0,handle_keypress,fractal->mlx);
	mlx_loop(fractal->mlx);
}
