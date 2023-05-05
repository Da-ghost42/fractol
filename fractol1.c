#include<mlx.h>
#include<math.h>


// #define HEIGHT 600
// #define WIDTH 800
// int main()
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     void *img_ptr;
//     void *data;
//     int bpp;
//     int line_z;
//     int endian;
//     int x,y,r,i = 0,j = 0;
//     int color;

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr,WIDTH,HEIGHT,"suiiiiiiiiercle");
//     img_ptr = mlx_new_image(mlx_ptr,WIDTH,HEIGHT);
//     data = mlx_get_data_addr(img_ptr,&bpp,&line_z,&endian);
//     x = WIDTH / 2;
//     y = HEIGHT / 2;
//     r = 250;
//     color = 0xFFFFFF;
//     while(i++ < WIDTH)
//     {
//         while(j++ < HEIGHT)
//         {
//             if (sqrt((i - x) * (i - x) + (j - y) * (j - y)) <= r)
//                 *(unsigned int *)(data + (j * line_z + i * (bpp / 8))) = color;
//         }
//     }
//     mlx_put_image_to_window(mlx_ptr,win_ptr,img_ptr,0,0);
//     mlx_loop(mlx_ptr);
// }
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define MAX_ITERATIONS 1000

typedef struct	s_complex
{
    double r;
    double i;
}               t_complex;

typedef struct  s_fractal
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    double  zoom;
    double  move_x;
    double  move_y;
}               t_fractal;

void ft_put_pixel(t_fractal *fractal, int x, int y, int color)
{
    char    *pixel;

    pixel = fractal->addr + (y * fractal->line_length + x * (fractal->bits_per_pixel / 8));
    *(unsigned int*)pixel = color;
}

int ft_get_color(int i)
{
    if (i == MAX_ITERATIONS)
        return (0);
    return ((int)round(255 * (double)i / MAX_ITERATIONS));
}

void ft_draw_fractal(t_fractal *fractal)
{
    int         x;
    int         y;
    t_complex   c;
    t_complex   z;
    int         i;
    int         color;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            c.r = 1.5 * (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->move_x;
            c.i = (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->move_y;
            z = (t_complex){0, 0};
            i = 0;
            while (z.r * z.r + z.i * z.i < 4 && i < MAX_ITERATIONS)
            {
                z = (t_complex){z.r * z.r - z.i * z.i + c.r, 2 * z.r * z.i + c.i};
                i++;
            }
            color = ft_get_color(i);
            ft_put_pixel(fractal, x, y, color << 16 | color << 8 | color);
        }
    }
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

int ft_key_hook(int keycode, t_fractal *fractal)
{
    if (keycode == 53)
        exit(0);
    else if (keycode == 24 || keycode == 27)
    {
        if (keycode == 24)
            fractal->zoom *= 1.1;
        else if (keycode == 27)
            fractal->zoom /= 1.1;
        ft_draw_fractal(fractal);
    }
    return (0);
}
