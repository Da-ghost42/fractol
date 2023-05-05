#include"fractol.h"

void init_mandel()
{

}


int main (int ac ,char **av)
{
    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr,WIDTH,HEIGHT,"Mandelbrot");
    // draw_mandelbrot_set(mlx_ptr,win_ptr);
    // mlx_loop(mlx_ptr);
    // return 0;
    if (ac != 2)
        printf("bad arguments");
    if (!ft_strncmp(av[1],"Mandelbrot",ft_strlen(av[1])))
        draw_mandelbort_set(mlx_ptr,win_ptr);
    if (!ft_strncmp(av[1],"Julia",ft_strlen(av[1])))
        draw_julia_set(mlx_ptr,win_ptr);
    
}
