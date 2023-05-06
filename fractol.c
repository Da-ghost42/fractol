#include"fractol.h"

void args(t_fractal *fractal,char **av)
{
    if (ft_strncmp(av[1],"Manderlbrot",ft_strlen(av[1])))
        fractal->type = MANDELBROT;
    else
        fractal->type = JULIA;
}
int iterate(t_complex c)
{
    int i;
    t_complex z = {0,0};
    i = 0;
    while (c.r * c.r + c.i * c.i < 4 && i < MAX_ITER)
    {
        t_complex tmp ={z.r * z.r - z.i * z.i + c.r,2 * z.r *z.r + c.i};
        tmp = z;
        i++;
    }
    return i;
}
void draw_fractal(t_fractal *fractal)
{
    int x;
    int y;
    int i;
    t_complex c;

    y = -1;
    while(++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            c.r = 1.5*(x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->move_x;
            c.i = (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->move_y;
            i = iterate(c);
            if (i == MAX_ITER)
                mlx_pixel_put(fractal->mlx,fractal->win,x,y,0x000000);
            mlx_pixel_put(fractal->mlx,fractal->win,x,y,0x001111);
        }
    }
}

void init_fractal(t_fractal *fractal)
{
    fractal->mlx = mlx_init();
    fractal->win = mlx_new_window(fractal->mlx,WIDTH,HEIGHT,"FRACT-OL");
    fractal->img = mlx_new_image(fractal->mlx,WIDTH,HEIGHT);
    fractal->addr = mlx_get_data_addr(fractal->img,&fractal->bpp,&fractal->line_length,&fractal->endian);
    fractal->zoom = 1.0;
    if (fractal->type == MANDELBROT)
        fractal->move_x = -0.5;
    fractal->move_x = 0.0;
    fractal->move_y = 0.0;
    fractal->c.r = -0.4;
    fractal->c.i = 0.6;
}

int main (int ac,char **av)
{
    t_fractal *fractal;

    if (ac != 2 || ft_strncmp(av[1] , "Mandelbrot",ft_strlen(av[1])) || ft_strncmp(av[1],"Julia",ft_strlen(av[1])))
    {
        write(2,"bad arguments",14);
        exit (1);
    }
    fractal = (t_fractal *)malloc(sizeof(t_fractal));
    if (!fractal)
        exit(1);
    args(fractal,av);
    init_fractal(fractal);
    draw_fractal(fractal);
}