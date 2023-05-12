/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:18:11 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/12 18:04:19 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

void set_pixel_color(t_fractal *fractal, int x, int y, int color)
{
    char *dst = fractal->addr + (y * fractal->line_length + x * (fractal->bpp / 8));
    *(unsigned int*)dst = color;
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


void get_guide(t_fractal *fractal)
{
    void *gui_win;

    gui_win = mlx_new_window(fractal->mlx, GUI_W, GUI_H, "GUIDE");

    mlx_string_put(fractal->mlx, gui_win, 10, 10, "Fractol GUIDE", 0xFFFFFF);
    mlx_string_put(fractal->mlx, gui_win, 10, 30, "Press ESC to quit", 0xFFFFFF);
    mlx_string_put(fractal->mlx, gui_win, 10, 50, "Press G for help", 0xFFFFFF);
}

int handle_keypress(int keycode, t_fractal *fractal)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(fractal->mlx, fractal->win);
        exit(0);
    }
    if (keycode == 48)
    {

        get_guide(fractal);
    }
    return 0;
}
int handle_mousepress(int keycode,int x,int y,t_fractal *fractal)
{
    if (keycode == MOUSE_UP)
        zoom_in(keycode,x,y,fractal);
}
int perform_iteration(t_complex c)
{
    int i = 0;
    t_complex z = { 0, 0 };
    while (z.r * z.r + z.i * z.i < 4 && i < MAX_ITER)
    {   
        t_complex tmp = {
            z.r * z.r - z.i * z.i + c.r,
            2 * z.r * z.i + c.i
        };
        z = tmp;
        i++;
    }
    return i;
}

// int julia_iterations(double x, double y, double cx, double cy) {
//     double zx = x;
//     double zy = y;
//     double new_zx, new_zy;

//     int i = 0;
//     while (i < MAX_ITER && (zx * zx + zy * zy) < 4.0) {
//         new_zx = zx * zx - zy * zy + cx;
//         new_zy = 2.0 * zx * zy + cy;
//         zx = new_zx;
//         zy = new_zy;
//         i++;
//     }
//     return i;
// }
int get_color(int i)
{
    if (i == MAX_ITER)
        return (0xFFFFFF);
    return (0xFFFFFF * i / 100);
}
void draw_fractal(t_fractal *fractal)
{
    // fractal->min_x = -1.5;
    // fractal->min_y = -1.0;
    // fractal->max_x = 0.5;
    // fractal->max_y = 1.0;
    int x,y;

    y = -1;
    while(++y < HEIGHT){
        x = -1;
        while(++x < WIDTH)
        {
            t_complex c = {
                1.5 * (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->move_x,
                (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->move_y
            };

            int i = perform_iteration(c);

            if (i == MAX_ITER)
                set_pixel_color(fractal,x,y,0x2874A6);
            else 
                set_pixel_color(fractal,x,y,0xFFFFFF * i / 100);
        }
    }

    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
// //     void draw_fractal(t_fractal *fractal)
// // {
//     double cx = (fractal->max_x + fractal->min_x) / 2;
//     double cy = (fractal->max_y + fractal->min_y) / 2;
//     double width = fractal->max_x - fractal->min_x;
//     double height = fractal->max_y - fractal->min_y;
//     double new_width = width / fractal->zoom;
//     double new_height = height / fractal->zoom;

//     fractal->min_x = cx - new_width / 2;
//     fractal->max_x = cx + new_width / 2;
//     fractal->min_y = cy - new_height / 2;
//     fractal->max_y = cy + new_height / 2;

//     int x, y;

//     for (y = 0; y < HEIGHT; y++) {
//         for (x = 0; x < WIDTH; x++) {
//             double re = fractal->min_x + (double)x / WIDTH * (fractal->max_x - fractal->min_x);
//             double im = fractal->min_y + (double)y / HEIGHT * (fractal->max_y - fractal->min_y);
//             t_complex c = { re, im };
//             int i = perform_iteration(c);
//             set_pixel_color(fractal, x, y, get_color(i));
//         }
//     }

//     mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}
int zoom_in(int keycode,int x,int y,t_fractal *fractal)
{
    double zoom_v = 1.1;
    double x_off = (double)(x - (WIDTH / 2)) / (double)(WIDTH / 2) * fractal->zoom;
    double y_off = (double)(y - (HEIGHT / 2)) / (double)(HEIGHT / 2) * fractal->zoom;
    
        fractal->zoom *= zoom_v;
        fractal->min_x += x_off/ fractal->zoom;
        fractal->min_y += y_off / fractal->zoom;
        draw_fractal(fractal);
    
    //  if (keycode == 4)
    // {
    //     double zoom_factor = 1.2;
    //     fractal->zoom *= zoom_factor;
    //     fractal->move_x += (x - WIDTH / 2) * (1.0 / WIDTH) / fractal->zoom * zoom_factor;
    //     fractal->move_y += (y - HEIGHT / 2) * (1.0 / HEIGHT) / fractal->zoom * zoom_factor;
    // }
    // else if (keycode == -1)
    // {
    //     double zoom_factor = 1.2;
    //     fractal->zoom /= zoom_factor;
    //     fractal->move_x -= (x - WIDTH / 2) * (1.0 / WIDTH) / fractal->zoom / zoom_factor;
    //     fractal->move_y -= (y - HEIGHT / 2) * (1.0 / HEIGHT) / fractal->zoom / zoom_factor;
    // }
    // draw_fractal(fractal);
    // return (0);
}
void init_fractal(t_fractal *fractal)
{
    fractal->mlx = mlx_init();
    fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "FRACT-OL");
    fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
    fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bpp, &fractal->line_length, &fractal->endian);
    fractal->zoom = 1.0;
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
        exit(1);

    fractal = (t_fractal *)malloc(sizeof(t_fractal));
    if (!fractal)
        return 0;
    set_fractal_type(fractal,av);
    if (fractal->type == 3)
        exit(1);
    // printf("--type%d",fractal->type);
    init_fractal(fractal);
    // draw_fractal(fractal);
    // mlx_hook(fractal->win,48,0,handle_keypress,fractal->mlx);
    mlx_hook(fractal->win,2,0,handle_keypress,fractal->mlx);
    // mlx_hook(fractal->win,4,0,handle_keypress,fractal->mlx);
    // mlx_hook(fractal->win,-1,0,handle_keypress,fractal->mlx);
    mlx_loop(fractal->mlx);
}
