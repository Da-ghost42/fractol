#include"fractol.h"

int main (int ac,char **av)
{
    t_fractal *fractal;

    if (ac != 2)
        write(2,"bad arguments",14);
    if (ft_strncmp(av[1],"Mandelbrot",ft_strlen(av[1])))
        draw_madelbrot_set(fractal);

}