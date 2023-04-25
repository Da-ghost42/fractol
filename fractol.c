// #include"fractol.h"

// // void my_mlx_put(t_data *data,int  x,int y,int color)
// // {
// //     char *dst;

// //     dst = data->addr + (y * data->line_length  + x * (data->bpp / 8));
// //     *(unsigned int*)dst = color;
// // }

// // int main()
// // {
// //     void *mlx_ptr;
// //     void *win_ptr;
// //     t_data data;
    
// //     mlx_ptr = mlx_init();
// //     win_ptr = mlx_new_window(mlx_ptr,1029,1000,"fractol");
// //     data.img = mlx_new_image(mlx_ptr,1920,1080);
// //     data.addr = mlx_get_data_addr(data.img,&data.bpp,&data.line_length,&data.endian);
// //     my_mlx_put(data.img,100,100,0x00FF0000);
// //     mlx_put_image_to_window(mlx_ptr,win_ptr,data.img,0,0);
// // }
// // #include "mlx.h"

// #define WIDTH 800
// #define HEIGHT 600

// typedef struct s_complex
// {
//     double r;
//     double i;
// } t_complex;

// int mandelbrot_iterations(t_complex c)
// {
//     t_complex z = {0, 0};
//     // printf("%f",z.i);
//     // printf("%f",z.r);
//     int i;
//     for (i = 0; i < 100 && z.r * z.r + z.i * z.i < 4; i++)
//     {
//         t_complex tmp = {z.r * z.r - z.i * z.i + c.r, 2 * z.r * z.i + c.i};
//         z = tmp;
//     }
//     return i;
// }

// void draw_mandelbrot_set(void *mlx_ptr, void *win_ptr)
// {
//     double zoom = 1.0;
//     double move_x = -0.5;
//     double move_y = 0;
//     int x, y;
//     for (y = 0; y < HEIGHT; y++)
//     {
//         for (x = 0; x < WIDTH; x++)
//         {
//             t_complex c = {1.5 * (x - WIDTH / 2) / (0.5 * zoom * WIDTH) + move_x,
//                            (y - HEIGHT / 2) / (0.5 * zoom * HEIGHT) + move_y};
//             int i = mandelbrot_iterations(c);
//             if (i == 1)
//                 mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x000000);
//             else
//                 mlx_pixel_put(mlx_ptr, win_ptr, x, y, i * 0x001111);
//         }
//     }
// }

// int main()
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Mandelbrot Set");
//     draw_mandelbrot_set(mlx_ptr, win_ptr);
//     mlx_loop(mlx_ptr);
//     return 0;
// }
#include "mlx.h"
#include <math.h>

// #define WIDTH 800
// #define HEIGHT 600

// int main()
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     void *img_ptr;
//     char *data;
//     int bpp;
//     int size_line;
//     int endian;
//     int x, y, r;
//     int color;

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Circle Drawing");
//     img_ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
//     data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

//     x = WIDTH / 2;   // x-coordinate of center of circle
//     y = HEIGHT / 2;  // y-coordinate of center of circle
//     r = 100;         // radius of circle
//     color = 0xFFFFFF; // white color

//     for (int i = 0; i < WIDTH; i++) {
//         for (int j = 0; j < HEIGHT; j++) {
//             if (sqrt((i - x) * (i - x) + (j - y) * (j - y)) <= r) {
//                 *(unsigned int *)(data + (j * size_line + i * (bpp / 8))) = color;
//             }
//         }
//     }

//     mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
//     mlx_loop(mlx_ptr);
//     return 0;
// }
#define HEIGHT 600
#define WIDTH 800
int main()
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    void *data;
    int bpp;
    int line_z;
    int endian;
    int x,y,r,i = 0,j = 0;
    int color;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr,WIDTH,HEIGHT,"suiiiiiiiiercle");
    img_ptr = mlx_new_image(mlx_ptr,WIDTH,HEIGHT);
    data = mlx_get_data_addr(img_ptr,&bpp,&line_z,&endian);
    x = WIDTH / 2;
    y = HEIGHT / 2;
    r = 250;
    color = 0xFF0000;
    while(i < WIDTH)
    {
        j = 0;
        while(j < HEIGHT)
        {
            if (sqrt(pow((i - x),2) + pow((j - y) , 2)) <= r && sqrt(pow((i - x),2) + pow((j - y) , 2)) >= r - 1)
                *(unsigned int *)(data + (j * line_z + i * (bpp / 8))) = color;
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(mlx_ptr,win_ptr,img_ptr,0,0);
    mlx_loop(mlx_ptr);
}