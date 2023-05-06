#ifndef FRACTOL_H
#define FRACTOL_H
#include<mlx.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include"lib/libft.h"

#define HEIGHT 600
#define WIDTH 800
#define MANDELBROT 1
#define JULIA 2
#define MAX_ITER 250

typedef struct s_complex
{
    double r;
    double i;
} t_complex;

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
    t_complex c;
    double move_x;
    double move_y;
    int    type;
}       t_fractal;

#endif
