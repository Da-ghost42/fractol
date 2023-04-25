#ifndef FRACTOL_H
#define FRACTOL_H
#include<mlx.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>

typedef struct s_data
{
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;

}       t_data;


#endif
