/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:18:18 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/18 12:57:13 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H
#include<mlx.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<complex.h>
#include"lib/libft.h"
#include"define.h"

#define HEIGHT 600
#define WIDTH 800
#define GUI_H 400
#define GUI_W 200
#define MANDELBROT 1
#define KEY_ESC 53
#define JULIA 2
#define MAX_ITER 1800

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
    char *addr;
    int bpp;
    int line_length;
    int endian;
    double zoom;
    t_complex c;
    double move_x;
    double move_y;
    // double r_julia;
    // double i_julia;
    double min_x;
    double min_y;
    double max_x;
    double max_y;
    int    type;
}       t_fractal;

#endif
