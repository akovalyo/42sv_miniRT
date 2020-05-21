#include "mlx.h"
#include "libft.h"

typedef struct  s_ptr {
    void        *mlx;
    void        *win;
}               t_ptr;

typedef	struct	s_draw
{
  int		x;
  int		y;
  int       color;
  int       x_len;
  int       y_len;
} t_draw;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

int deal_key(int key, t_ptr *ptr)
{
    // t_ptr *window;
    // window = param;
    
    // ft_printf("%d\n", key);
    // ft_printf("%p\n", window->mlx_ptr);
    // ft_printf("%p\n", window->win_ptr);
    if (key == 65307)
        mlx_destroy_window(ptr->mlx, ptr->win);
    return (0);
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int data_offset(t_data *data, int x, int y)
{
    return (y * data->line_length + x * (data->bits_per_pixel / 8));
}

void mlx_pixel_to_image(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + data_offset(data, x, y);
    *(unsigned int *)dst = color;
}

void draw_line(t_data *data, t_draw *draw)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < draw->x_len)
    {
        mlx_pixel_to_image(data, draw->x + x, draw->y, draw->color);
        if (x <= draw->x_len)
            x++;

    }
}

void render_next_frame(t_data *data, t_draw *draw)
{

}

int main()
{
    // void *mlx_ptr;
    // void *win_ptr;
    t_data img;
    t_draw draw;
    int offset;
    t_ptr ptr;
    int j = 0;
    
    // void *v_ptr;
    
    // window.mlx_ptr = mlx_ptr;
    // ft_printf("%d\n",1);
    // window.win_ptr = win_ptr;
    // v_ptr = &window;

    //ft_printf("%s\n", test);
    //ft_putnbr(-2147483648);
    ptr.mlx = mlx_init();
    img.img = mlx_new_image(ptr.mlx, 500, 500);
    ptr.win = mlx_new_window(ptr.mlx, 500, 500, "Hello World!");
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    
    draw.x = 100;
    draw.y = 100;
    draw.x_len = 100;
    draw.y_len = 0;
    draw.color = create_trgb(0,255,0,0);

    for (int i = 0; i < 100; i++)
    {    
        
        draw_line(&img, &draw);
        draw.y++;
        
    }
    mlx_put_image_to_window(ptr.mlx, ptr.win, img.img, 0, 0);
    ft_printf("%d\n", draw.color);
    // ft_printf("%d\n",2);
    // mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
    //mlx_loop_hook(ptr.mlx, render_next_frame, &ptr);
        //mlx_destroy_window(mlx_ptr, win_ptr);
    mlx_loop(ptr.mlx);
    return (0);
}