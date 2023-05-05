#ifndef FRACTOL_H
#define FRACTOL_H
#include<mlx.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include"lib/libft.h"

#define HEIGHT 600
#define WIDTH 800

typedef struct s_fractal
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;
    double zoom;
    double move_x;
    double move_y;
}       t_fractal;

typedef struct s_complex
{
    double r;
    double i;
} t_complex;
#endif
