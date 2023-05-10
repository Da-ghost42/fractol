#include"fractol.h"

// void	my_mlx_pixel_put(t_fractal *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
// 	*(unsigned int*)dst = color;
// }

// void args(t_fractal *fractal,char **av)
// {
//     if (!ft_strncmp(av[1],"Mandelbrot",ft_strlen(av[1])))
//         fractal->type = MANDELBROT;
//     if (!ft_strncmp(av[1],"Julia",ft_strlen(av[1])))
//         fractal->type = JULIA;
// }
// int iterate(t_complex c)
// {
//     int i;
//     double xtemp;
//     t_complex z = {0,0};
//     i = 0;
//     while (z.r * z.r + z.i * z.i < 4 && i < MAX_ITER)
//     {
//         t_complex tmp ={z.r * z.r - z.i * z.i + c.r,    2 * z.r *z.r + c.i};
//         z = tmp;
//         //  xtemp = z.r * z.r - z.i * z.i + c.r;
//         // z.i = 2 * z.r *z.r + c.i;
//         // z.r = xtemp;
//         i++;
//     }
//     return i;
// }
// void draw_fractal(t_fractal *fractal)
// {
//     int x;
//     double xmin = -1.5;
//     double ymin = -1.0;
//     double xmax = 0.5;
//     double ymax = 1.0;
//     int y;
//     int i;
//     // t_complex c;

//     y = -1;
//     while(++y < HEIGHT)
//     {
//         x = -1;
//         while (++x < WIDTH)
//         {
//             // c.r = xmin + x*(xmax-xmin)/ HEIGHT;
// 			// c.i = ymin + y*(ymax-ymin)/WIDTH;
//             t_complex c = {
//                 1.5 * (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->move_x,
//                 (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->move_y};
//             // c.r = 1.5 * (x - WIDTH / 2) / (fractal->zoom * WIDTH) + fractal->move_x;
//             // c.i = (y - HEIGHT / 2) / (fractal->zoom * HEIGHT) + fractal->move_y;
//             // c.r =(x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->move_x;
//             // c.i = (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->move_y;
//             // printf("--x%d\n",x);
//             // printf("--y%d\n",y);
//             i = iterate(c);
//             // printf("--i%d\n",i);
//             if (i == MAX_ITER)
//                 my_mlx_pixel_put(fractal,x,y,0xFFFFFF);
//             else 
//                 my_mlx_pixel_put(fractal,x,y,i * 256 / MAX_ITER);
//         }
//     }
//         mlx_put_image_to_window(fractal->mlx,fractal->win,fractal->img,0,0);
//     // Set the image buffer to 0
//     // memset(fractal->addr, 0, WIDTH * HEIGHT * (fractal->bpp / 8));

//     // // Calculate the complex number c
//     // t_complex c = {fractal->c.r, fractal->c.i};

//     // // Iterate over the pixels and set their color based on the number of iterations
//     // for (int y = 0; y < HEIGHT; y++)
//     // {
//     //     for (int x = 0; x < WIDTH; x++)
//     //     {
//     //         // Calculate the complex number corresponding to the current pixel
//     //         t_complex z = {
//     //             1.5 * (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->move_x,
//     //             (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->move_y
//     //         };

//     //         // Iterate and count the number of iterations before the sequence diverges
//     //         int i = iterate(fractal->type == JULIA ? z : c);

//     //         // Set the pixel color based on the number of iterations
//     //         int color = (i == MAX_ITER ? 0xFFFFFF : i * 256 / MAX_ITER);
//     //         my_mlx_pixel_put(fractal, x, y, color);
//     //     }
//     // }

//     // // Update the window with the new image
//     // mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
// }


// void init_fractal(t_fractal *fractal)
// {
//     fractal->mlx = mlx_init();
//     fractal->win = mlx_new_window(fractal->mlx,WIDTH,HEIGHT,"FRACT-OL");
//     fractal->img = mlx_new_image(fractal->mlx,WIDTH,HEIGHT);
//     fractal->addr = mlx_get_data_addr(fractal->img,&fractal->bpp,&fractal->line_length,&fractal->endian);
//     fractal->zoom = 0.5;
//     if (fractal->type == MANDELBROT)
//         fractal->move_x = 0.75;
//     else
//         fractal->move_x = 0.5;
//     fractal->move_y = -1.5;
//     fractal->c.r = -0.4;
//     fractal->c.i = 0.6;
// }
// This function sets the color of a pixel in the fractal image
void set_pixel_color(t_fractal *fractal, int x, int y, int color)
{
    char *dst = fractal->addr + (y * fractal->line_length + x * (fractal->bpp / 8));
    *(unsigned int*)dst = color;
}
int handle_keypress(int keycode,t_fractal *fractal)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(fractal->mlx,fractal->win);
        exit (0);
    }
    return 0;
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
void draw_fractal(t_fractal *fractal)
{
    double xmin = -1.5;
    double ymin = -1.0;
    double xmax = 0.5;
    double ymax = 1.0;
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
}
void init_fractal(t_fractal *fractal)
{
    fractal->mlx = mlx_init();
    fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "FRACT-OL");
    fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
    fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bpp, &fractal->line_length, &fractal->endian);
    fractal->zoom = 1.0;
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
    draw_fractal(fractal);
    mlx_hook(fractal->win,2,0,handle_keypress,fractal->mlx);
    mlx_loop(fractal->mlx);
}
// #include "mlx.h"

// // #define WIDTH 1000
// // #define HEIGHT 1000

// // typedef struct s_complex
// // {
// //     double r;
// //     double i;
// // } t_complex;

// int iterate_mandelbrot(t_complex c)
// {
//     int max_iter = 100;
//     t_complex z = {0, 0};
//     int i;
//     for (i = 0; i < max_iter; i++)
//     {
//         if (z.r * z.r + z.i * z.i > 4)
//             break;
//         t_complex z_new = {z.r * z.r - z.i * z.i + c.r, 2 * z.r * z.i + c.i};
//         z = z_new;
//     }
//     return i;
// }

// int get_color(int iter)
// {
//     if (iter == 100)
//         return 0x000000; // Black
//     else
//         return 0xFFFFFF * iter / 100; // Varying shades of white
// }

// int main()
// {
//     int bpp;
//     int size_line;
//     int endian;
//     void *mlx = mlx_init();
//     void *window = mlx_new_window(mlx, WIDTH, HEIGHT, "Mandelbrot Set");
//     void *image = mlx_new_image(mlx, WIDTH, HEIGHT);
//     int *data = (int *)mlx_get_data_addr(image, &bpp, &size_line, &endian);

//     t_complex min = {-2, -1.5};
//     t_complex max = {1, 1.5};
//     double dx = (max.r - min.r) / (double)WIDTH;
//     double dy = (max.i - min.i) / (double)HEIGHT;

//     int x, y;
//     for (y = 0; y < HEIGHT; y++)
//     {
//         for (x = 0; x < WIDTH; x++)
//         {
//             t_complex c = {min.r + x * dx, min.i + y * dy};
//             int iter = iterate_mandelbrot(c);
//             int color = get_color(iter);
//             data[y * WIDTH + x] = color;
//         }
//     }

//     mlx_put_image_to_window(mlx, window, image, 0, 0);
//     mlx_loop(mlx);
// }
