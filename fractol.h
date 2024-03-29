/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutuil <mboutuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:18:18 by mboutuil          #+#    #+#             */
/*   Updated: 2023/05/23 15:59:12 by mboutuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include<mlx.h>
# include<stdio.h>
# include<unistd.h>
# include<math.h>
# include<complex.h>
# include"lib/libft.h"
# include"define.h"
# define SIZE 600
# define GUI_H 400
# define GUI_W 200
# define MANDELBROT 1
# define KEY_ESC 53
# define JULIA 2
# define MAX_ITER 150

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_fractal
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*gui;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	double		zoom;
	int			i;
	t_complex	ju;
	t_complex	c;
	double		min_x;
	double		min_y;
	double		max_x;
	double		max_y;
	int			iter;
	int			type;
	int			lock;
}	t_fractal;
//FUNCTIONS
void		init_fractol(t_fractal *fractal, int set);
void		draw_fractal(t_fractal *fractal);
int			key_set(int keycode, t_fractal *fractal);
int			keypress_set(t_fractal *fractal);
int			mouse_set(int keycode, int x, int y, t_fractal *fractal);
int			zoom_out(int x, int y, t_fractal *fractal);
int			zoom_in(int x, int y, t_fractal *fractal);
void		set_pix_color(t_fractal *fractal, int x, int y, int color);
int			zoom_out(int x, int y, t_fractal *fractal);
int			zoom_in(int x, int y, t_fractal *fractal);
void		init_mandel(t_fractal *fractal);
int			iteration(t_complex c, t_fractal *fractal);
void		draw_fractal(t_fractal *fractal);
int			get_color(t_fractal *fractal, int i);
void		init_julia(t_fractal *fractal);
void		draw_julia(t_fractal *fractal);
int			arrows(int keycode, t_fractal *fractal);
void		hooks(t_fractal *fractal);
void		draw_mandel(t_fractal *fractal);
t_complex	which_julia(t_fractal *fractal);
int			animate(int x, int y, t_fractal *fractal);
void		draw_burn(t_fractal *fractal);
int			iteration_burn(t_complex c, t_fractal *fractal);
void		init_burn(t_fractal *fractal);

#endif
