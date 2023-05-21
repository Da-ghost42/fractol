/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:18:18 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/21 15:11:01 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H
#include<mlx.h>
#include<stdio.h>
// # include <X11/keysym.h>
// #include<X11/X.h>
#include<unistd.h>
#include<math.h>
#include<complex.h>
#include"lib/libft.h" 
#include"define.h"
                      
#define HEIGHT 600
#define WIDTH 600
#define GUI_H 400
#define GUI_W 200
#define MANDELBROT 1
#define KEY_ESC 53
#define JULIA 2
#define MAX_ITER 150

typedef struct s_complex    
{
    double r;
    double i;
} t_complex; 

typedef struct c_sample
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} t_sample;

typedef struct s_fractal
{
    void *mlx;
    void *win;
    void *img;
    void *gui;
    int i;
    int j;
    char *addr;
    int bpp;
    int line_length;
    int endian;
    double zoom;
    t_complex c;
    t_complex  ju;
    double move_x;
    double move_y;
    double min_x;
    double min_y;
    double max_x;
    double max_y;
    int     iter;
    int    type;
}       t_fractal;
void    draw_fractal(t_fractal *fractal);
#endif
