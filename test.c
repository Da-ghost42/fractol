/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:18:32 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/12 17:48:52 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include"fractol.h"

// void init_mandel()
// {

// }


// int main (int ac ,char **av)
// {
//     void *mlx_ptr;
//     void *win_ptr;

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr,WIDTH,HEIGHT,"Mandelbrot");
//     // draw_mandelbrot_set(mlx_ptr,win_ptr);
//     // mlx_loop(mlx_ptr);
//     // return 0;
//     if (ac != 2)
//         printf("bad arguments");
//     if (!ft_strncmp(av[1],"Mandelbrot",ft_strlen(av[1])))
//         draw_mandelbort_set(mlx_ptr,win_ptr);
//     if (!ft_strncmp(av[1],"Julia",ft_strlen(av[1])))
//         draw_julia_set(mlx_ptr,win_ptr);
    
// }
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void draw_fractal(t_fractal *fractal)
{
    double xmin = -1.5;
    double ymin = -1.0;
    double xmax = 0.5;
    double ymax = 1.0;
    int x, y;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            t_complex c = {
                1.5 * (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->move_x,
                (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->move_y
            };

            int i = perform_iteration(c);

            if (i == MAX_ITER)
                set_pixel_color(fractal, x, y, 0x2874A6);
            else
                set_pixel_color(fractal, x, y, 0xFFFFFF * i / 100);
        }
    }

    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

int handle_mousepress(int button, int x, int y, t_fractal *fractal)
{
    if (button == MOUSE_SCROLL_UP)
    {
        double zoom_factor = 1.2;
        fractal->zoom *= zoom_factor;
        fractal->move_x += (x - WIDTH / 2) * (1.0 / WIDTH) / fractal->zoom * zoom_factor;
        fractal->move_y += (y - HEIGHT / 2) * (1.0 / HEIGHT) / fractal->zoom * zoom_factor;
    }
    else if (button == MOUSE_SCROLL_DOWN)
    {
        double zoom_factor = 1.2;
        fractal->zoom /= zoom_factor;
        fractal->move_x -= (x - WIDTH / 2) * (1.0 / WIDTH) / fractal->zoom / zoom_factor;
        fractal->move_y -= (y - HEIGHT / 2) * (1.0 / HEIGHT) / fractal->zoom / zoom_factor;
    }
    draw_fractal(fractal);
    return (0);
}

int main ()
{
    pthread_t thread1,thread2;

    char *p = "hello";
    char *s = "world";

    pthread_create(&thread1,NULL,print_message,(void *)p);
    pthread_create(&thread2,NULL,print_message,(void *)s);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    return 0;

}