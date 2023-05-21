#include"fractol.h"

void	set_pix_color(t_fractal *fractal,int x,int y,int color)
{
	char	*dst;

	dst = fractal->addr + (y * fractal->line_length + x * (fractal->bpp / 8));
	*(unsigned int*)dst = color;
}

int zoom_out(int x, int y, t_fractal *fractal)
{
	double j;
	double i;

	i = fractal->min_x + x * (fractal->max_x - fractal->min_x) / WIDTH;
	j = fractal->min_y + y * (fractal->max_y - fractal->min_y) / HEIGHT;
	fractal->min_x /= fractal->zoom;
	fractal->max_x /= fractal->zoom;
	fractal->min_y /= fractal->zoom;
	fractal->max_y /= fractal->zoom;
	fractal->min_x -= i;
	fractal->max_x -= i;
	fractal->min_y -= j;
	fractal->max_y -= j;
	fractal->iter -= 10;

    draw_fractal(fractal);
    return 0;
}

int zoom_in(int x, int y, t_fractal *fractal)
{
	double j;
	double i;

	i = fractal->min_x + x * (fractal->max_x - fractal->min_x) / WIDTH;
	j = fractal->min_y + y * (fractal->max_y - fractal->min_y) / HEIGHT;
	fractal->min_x += i;
	fractal->max_x += i;
	fractal->min_y += j;
	fractal->max_y += j;
	fractal->min_x *= fractal->zoom;
	fractal->max_x *= fractal->zoom;
	fractal->min_y *= fractal->zoom;
	fractal->max_y *= fractal->zoom;
	fractal->iter += 10;
    draw_fractal(fractal);
    return 0;
}
int	get_color(int i)
{
	 int	r;
	 int	g;
	 int	b;

	 r = i % 256;
	 g = (i * 2) % 256;
	 b = (i * 3) % 256;

	 return ((r << 16) | (g << 8) | b);
}
