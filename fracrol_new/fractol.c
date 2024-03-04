#include <mlx.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

unsigned char	get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    draw_rainbow(t_data *img, int width, int height) {
    int x, y;
    float ratio;
    for (y = 0; y < height; y++) {
        ratio = (float)y / height;
        for (x = 0; x < width; x++) {
			ratio = (float)x / width;
            int red = (int)(255 * ratio);
            int green = (int)(255 * (1 - fabs(ratio - 0.5) * 2));
            int blue = (int)(255 * (1 - ratio));
            int color = (red << 16) | (green << 8) | blue;
            my_mlx_pixel_put(img, x, y, color);
        }
    }
}


void draw_square(t_data *img, int x_start, int y_start, int size, int color) {
    for (int y = y_start; y < y_start + size; y++) {
        for (int x = x_start; x < x_start + size; x++) {
            my_mlx_pixel_put(img, x, y, color);
        }
    }
}
void draw_line(t_data *img, int x0, int y0, int x1, int y1, int color) {
    int dx, dy, p, x, y;

    dx=x1-x0;
    dy=y1-y0;

    x=x0;
    y=y0;

    p=2*dy-dx;

    while(x<x1) {
        if(p>=0) {
            my_mlx_pixel_put(img, x, y, color);
            y=y+1;
            p=p+2*dy-2*dx;
        } else {
            my_mlx_pixel_put(img, x, y, color);
            p=p+2*dy;
        }
        x=x+1;
    }
}
void draw_circle(t_data *img, int xc, int yc, int x, int y, int color) {
	my_mlx_pixel_put(img, xc+x, yc+y, color);
	my_mlx_pixel_put(img, xc-x, yc+y, color);
	my_mlx_pixel_put(img, xc+x, yc-y, color);
	my_mlx_pixel_put(img, xc-x, yc-y, color);
	my_mlx_pixel_put(img, xc+y, yc+x, color);
	my_mlx_pixel_put(img, xc-y, yc+x, color);
	my_mlx_pixel_put(img, xc+y, yc-x, color);
	my_mlx_pixel_put(img, xc-y, yc-x, color);
}
void add_shade(t_data *img, int x, int y, int color, float shade) {
	int trgb = create_trgb(get_t(color), get_r(color) * shade, get_g(color) * shade, get_b(color) * shade);
	my_mlx_pixel_put(img, x, y, trgb);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int width = 500;
	int height = 500;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1080, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1080, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	// int x0 = 100, y0 = 100;
    // int x1 = 150, y1 = 200;
    // int x2 = 50, y2 = 200;

	// draw_line(&img, x0, y0, x1, y1, 0x00FF0000); // От первой вершины ко второй
    // draw_line(&img, x1, y1, x2, y2, 0x00FF0000); // От второй вершины к третьей
    // draw_line(&img, x2, y2, x0, y0, 0x00FF0000);
	draw_square(&img, 100, 100, 300, 0x003333FF);
	//draw_circle(&img, 100, 100, 50, 0, 0x00FF0000);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0400);
	//draw_rainbow(&img, width, height);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
