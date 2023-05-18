#include"fractol.h"

void get_guide(t_fractal *fractal)
{
	void *gui_win;

	gui_win = mlx_new_window(fractal->mlx, GUI_W, GUI_H, "GUIDE");

	mlx_string_put(fractal->mlx, gui_win, 10, 10, "Fractol GUIDE", 0xFFFFFF);
	mlx_string_put(fractal->mlx, gui_win, 10, 30, "Press ESC to quit", 0xFFFFFF);
	mlx_string_put(fractal->mlx, gui_win, 10, 50, "Press G for help", 0xFFFFFF);
}

int zoom_in(int keycode,int x,int y,t_fractal *fractal)
{
	double zoom_v = 1.1;
	double x_off = (double)(x - (WIDTH / 2)) / (double)(WIDTH / 2) * fractal->zoom;
	double y_off = (double)(y - (HEIGHT / 2)) / (double)(HEIGHT / 2) * fractal->zoom;
	
		fractal->zoom *= zoom_v;
		fractal->min_x += x_off/ fractal->zoom;
		fractal->min_y += y_off / fractal->zoom;
		draw_fractal(fractal);
	
	//  if (keycode == 4)
	// {
	//     double zoom_factor = 1.2;
	//     fractal->zoom *= zoom_factor;
	//     fractal->move_x += (x - WIDTH / 2) * (1.0 / WIDTH) / fractal->zoom * zoom_factor;
	//     fractal->move_y += (y - HEIGHT / 2) * (1.0 / HEIGHT) / fractal->zoom * zoom_factor;
	// }
	// else if (keycode == -1)
	// {
	//     double zoom_factor = 1.2;
	//     fractal->zoom /= zoom_factor;
	//     fractal->move_x -= (x - WIDTH / 2) * (1.0 / WIDTH) / fractal->zoom / zoom_factor;
	//     fractal->move_y -= (y - HEIGHT / 2) * (1.0 / HEIGHT) / fractal->zoom / zoom_factor;
	// }
	// draw_fractal(fractal);
	// return (0);
}
int handle_mousepress(int keycode,int x,int y,t_fractal *fractal)
{
	if (keycode == MOUSE_UP)
		zoom_in(keycode,x,y,fractal);
}

// int julia_iterations(double x, double y, double cx, double cy) {
//     double zx = x;
//     double zy = y;
//     double new_zx, new_zy;

//     int i = 0;
//     while (i < MAX_ITER && (zx * zx + zy * zy) < 4.0) {
//         new_zx = zx * zx - zy * zy + cx;
//         new_zy = 2.0 * zx * zy + cy;
//         zx = new_zx;
//         zy = new_zy;
//         i++;
//     }
//     return i;
// }