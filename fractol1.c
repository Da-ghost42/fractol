#include<mlx.h>
#include<math.h>


#define HEIGHT 600
#define WIDTH 800
int main()
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    void *data;
    int bpp;
    int line_z;
    int endian;
    int x,y,r,i = 0,j = 0;
    int color;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr,WIDTH,HEIGHT,"suiiiiiiiiercle");
    img_ptr = mlx_new_image(mlx_ptr,WIDTH,HEIGHT);
    data = mlx_get_data_addr(img_ptr,&bpp,&line_z,&endian);
    x = WIDTH / 2;
    y = HEIGHT / 2;
    r = 250;
    color = 0xFFFFFF;
    while(i++ < WIDTH)
    {
        while(j++ < HEIGHT)
        {
            if (sqrt((i - x) * (i - x) + (j - y) * (j - y)) <= r)
                *(unsigned int *)(data + (j * line_z + i * (bpp / 8))) = color;
        }
    }
    mlx_put_image_to_window(mlx_ptr,win_ptr,img_ptr,0,0);
    mlx_loop(mlx_ptr);
}
