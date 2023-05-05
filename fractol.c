#include<mlx.h>
#include<math.h>
#include"fractol.h"


// void ft_ellipse(int x ,int y,int r,int size_l,int bpp,void *data)
// {
//     int i = 0;
//     int j = 0;
//     int color = 0xFF0000;

//     // r = 250;
//     while(i < WIDTH)
//     {
//         j = 0;
//         while(j < HEIGHT)
//         {
//             if (sqrt(pow(i - x,2)) + pow(j - y,2) <= r && sqrt(pow(i - x,2)) + pow(j - y,2) >= r - 1)
//                 *(unsigned int *)(data + (j * size_l + i * (bpp / 8))) = color;
//             j++;
//         }
//         i++;
//     }
// }
// void ft_drawcs(void *data,int x,int y,int r)
// {



// }
// void ft_draw_circle(int size_l,int bpp,void *data)
// {
//     int i = 0;
//     int j = 0;

//    int x = WIDTH / 2;
//    int y = HEIGHT / 2;
//    int r = 80;
//    int color = 0xFF0000;

//     while(i < WIDTH)
//     {
//         j = 0;
//         while(j < HEIGHT)
//         {
//             if (sqrt(pow(i - x,2) + pow(j - y,2)) <= r && sqrt(pow(i - x,2) + pow(j - y,2)) >= r - 1)
//                 *(unsigned int *)(data + (j * size_l + i * (bpp / 8))) = color;
//             j++;
//         }
//         i++;
//     }
//    }

// int main()
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     void *img_ptr;
//     void *data;
//     int bpp;
//     int line_z;
//     int endian;

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr,WIDTH,HEIGHT,"suiiiiiiiiercle");
//     img_ptr = mlx_new_image(mlx_ptr,WIDTH,HEIGHT);
//     data = mlx_get_data_addr(img_ptr,&bpp,&line_z,&endian);
//     ft_draw_circle(line_z,bpp,data);
//     mlx_put_image_to_window(mlx_ptr,win_ptr,img_ptr,0,0);
//     mlx_loop(mlx_ptr);
// }
///////////////
// void ft_drawc_ircle(void *img,int x,int y,int r,int color)
// {
//     void *data;
//     int i = 0,j = 0;
//     int bpp;
//     int endian;
//     int line_s;

//     data = mlx_get_data_addr(img, &bpp,&line_s,&endian);
//      while(i < WIDTH)
//     {
//         j = 0;
//         while(j < HEIGHT)
//         {
//             if (sqrt(pow(i - x,2)) + pow(j - y,2) <= r && sqrt(pow(i - x,2)) + pow(j - y,2) >= r - 1)
//                 *(unsigned int *)(data + (j * line_s + i * (bpp / 8))) = color;
//             j++;
//         }
//         i++;
//     }
// }
// void ft_draw_cs(void *img,int x,int y,int r,int color, int num)
// {
//     // color = 0xFFFFFF;
//     ft_drawc_ircle(img,x,y,r,color);
//     if (num > 1)
//     {
//         ft_draw_cs(img,x + r,y,r/2,color * 2,num - 1);
//         ft_draw_cs(img,x - r,y,r/2,color * 3,num - 1);
//         ft_draw_cs(img,x,y + r,r/2,color * 4,num - 1);
//         ft_draw_cs(img,x,y - r,r/2,color * 5,num - 1);
//     }
// }
// int main ()
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     void *img_ptr;
//     int color = 0xFFFFFF;
//     // void *data_ptr;

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr,WIDTH,HEIGHT,"TRYHARD");
//     img_ptr = mlx_new_image(mlx_ptr,WIDTH,HEIGHT);
//     ft_draw_cs(img_ptr,WIDTH / 2,HEIGHT / 2,250,color,3);
//     mlx_put_image_to_window(mlx_ptr,win_ptr,img_ptr,0,0);
//     mlx_loop(mlx_ptr);
// }
// #include "mlx.h"

// #define WIDTH 800
// #define HEIGHT 600

int mandelbrot_iterations(t_complex c)
{
    t_complex z = {0, 0};
    int i;
    for (i = 0; i < 150 && z.r * z.r + z.i * z.i <  4; i++)
    {
        t_complex tmp = {z.r * z.r - z.i * z.i + c.r, 2 * z.r * z.i + c.i};
        z = tmp;
    }
    return i;
}

void draw_mandelbrot_set(void *mlx_ptr, void *win_ptr)
{
    double zoom = 1.0;
    double move_x = -0.5;
    double move_y = 0;
    int x, y;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            t_complex c = {1.5 * (x - WIDTH / 2) / (0.5 * zoom * WIDTH) + move_x,
                           (y - HEIGHT / 2) / (0.5 * zoom * HEIGHT) + move_y};
            int i = mandelbrot_iterations(c);
            if (i == 150)
                mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000000);
            else
                mlx_pixel_put(mlx_ptr, win_ptr, x, y, i * 0x800080);
        }
    }
}

int main()
{
    void *mlx_ptr;
    void *win_ptr;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Mandelbrot Set");
    draw_mandelbrot_set(mlx_ptr, win_ptr);
    mlx_loop(mlx_ptr);
    return 0;
}

// void    check_args(char *av)
// {
//     if (ft_strncmp(av,"Mandelbort",11))
//         get_mandel();
//     else 
//         exit(0);
// }
// int main (int ac ,char **av)
// {
//     if (ac > 2)
//         write (1,"bad arguments number",21);
//     check_args(*av);
// }