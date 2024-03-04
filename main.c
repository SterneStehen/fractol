# include "fractol.h"


static void malloc_error(void)
{
	ft_putstr_fd("Malloc error\n", 1);
	exit(EXIT_FAILURE);
}

double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
	return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min);
}

t_complex sum_comlex(t_complex z1, t_complex z2)
{
	t_complex result;
	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result);
}

t_complex square_complex(t_complex z)
{
	t_complex result;
	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}

void data_init(t_fractol *fractol)
{
	fractol->escape_value = 4;
	fractol->iterations_defintion = 42;
	// fractol->zoom = 1.0f;
	// fractol->x_shift = 0.0f;
	// fractol->y_shift = 0.0f;
	// fractol->min.x = -2.0f;
	// fractol->min.y = -1.0f;
	// fractol->max.x = 1.0f;
	// fractol->max.y = 1.0f;
}

static void my_pixel_put(int x, int y, t_img *img, int color)
{
	int offset;
	offset = (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)(img->pixwls_ptr + offset) = color;
}

static void handle_pixel(int x, int y, t_fractol *fractol)
{
    t_complex z = {0.0, 0.0};
    t_complex c;
    c.x = map(x, -2, +2, 0, WIDTH);
    c.y = map(y, +2, -2, 0, HEIGHT);
    int color;
    int i = 0;

    while (i < fractol->iterations_defintion)
    {
        z = sum_comlex(square_complex(z), c);
        if ((z.x * z.x) + (z.y * z.y) > fractol->escape_value)
        {
            color = map(i, BLACK, WHITE, 0, fractol->iterations_defintion);
            printf("Pixel [%d, %d] escapes at iteration %d with color %x\n", x, y, i, color);
            my_pixel_put(x, y, &fractol->img, color);
            return;
        }
        i++;
    }
    my_pixel_put(x, y, &fractol->img, PSYCHEDELIC_PURPLE);
}


// static void handle_pixel(int x, int y, t_fractol *fractol)
// {
// 	t_complex z;
// 	t_complex c;
// 	int color;
// 	int i;
// 	i = 0;
// 	z.x = 0.0;
// 	z.y = 0.0;

// 	// c.x = map(x, -2, +2, 0, WIDTH);
// 	// c.y = map(y, +2, -2, 0, HEIGHT);

// 	c.x = map(x, 0, WIDTH, -2, 1); // Экран -> Комплексная плоскость
// 	c.y = map(y, 0, HEIGHT, -1, 1); // Экран -> Комплексная плоскость


// 	while (i < fractol->iterations_defintion)
// 	{
// 		z = sum_comlex(square_complex(z), c);
// 		if ((z.x * z.x) + (z.y * z.y) > fractol->escape_value)
// 		{
// 			// color = map(i, BLACK, WHITE, 0, fractol->iterations_defintion);
// 			color = map(i, 0, fractol->iterations_defintion, BLACK, WHITE);
// 			my_pixel_put(x, y, &fractol->img, color);
// 			return;
// 		}
// 		i++;
// 	}
// 	my_pixel_put(x, y, &fractol->img, PSYCHEDELIC_PURPLE);	
// 	//*(unsigned int *)(fractol->img.pixwls_ptr + (y * fractol->img.line_length + x * (fractol->img.bpp / 8))) = color;
// }	

void fractol_render(t_fractol *fractol)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractol);
		}
	}
	mlx_put_image_to_window(fractol->mlx_connection, fractol->mlx_window, fractol->img.img_ptr, 0, 0);
}

void fractol_init(t_fractol *fractol)
{
    fractol->mlx_connection = mlx_init();
    if (NULL == fractol->mlx_connection)
    {
        printf("Failed to initialize mlx.\n");
        malloc_error();
    }
    printf("mlx initialized successfully.\n");

    fractol->mlx_window = mlx_new_window(fractol->mlx_connection, WIDTH, HEIGHT, fractol->name);
    if (NULL == fractol->mlx_window)
    {
        printf("Failed to create window.\n");
        mlx_destroy_display(fractol->mlx_connection);
        free(fractol->mlx_connection);
        malloc_error();
    }
    printf("Window created successfully. Width: %d, Height: %d\n", WIDTH, HEIGHT);

    fractol->img.img_ptr = mlx_new_image(fractol->mlx_connection, WIDTH, HEIGHT);
    if (NULL == fractol->img.img_ptr)
    {
        printf("Failed to create image.\n");
        mlx_destroy_window(fractol->mlx_connection, fractol->mlx_window);
        mlx_destroy_display(fractol->mlx_connection);
        free(fractol->mlx_connection);
        malloc_error();
    }
    printf("Image created successfully.\n");

    fractol->img.pixwls_ptr = mlx_get_data_addr(fractol->img.img_ptr, &fractol->img.bpp, &fractol->img.line_length, &fractol->img.endian);
    printf("Image data address obtained successfully.\n");
	data_init(fractol);
	printf("Data initialized successfully.\n");
	// fractol->max_iter = 50;
	// fractol->zoom = 1.0f;
	// fractol->x_shift = 0.0f;
	// fractol->y_shift = 0.0f;
	// fractol->min.real = -2.0f;
	// fractol->min.img = -1.0f;
	// fractol->max.real = 1.0f;
	// fractol->max.img = 1.0f;
	// fractol->fractal = mandelbrot;
	printf("Fractol initialized successfully.\n");
}


// void fractol_init(t_fractol *fractol)
// {
// 	fractol->mlx_connection = mlx_init();
// 	if (NULL == fractol->mlx_connection)
// 	{
// 		malloc_error();
// 	}
// 	fractol->mlx_window = mlx_new_window(fractol->mlx_connection, WIDTH, HEIGHT, fractol->name);
// 	if (NULL == fractol->mlx_window)
// 	{
// 		//mlx_destroy_window(fractol->mlx_connection, fractol->mlx_window);
// 		mlx_destroy_display(fractol->mlx_connection);
// 		free(fractol->mlx_connection);
// 		malloc_error();
// 	}
// 	fractol->img.img_ptr = mlx_new_image(fractol->mlx_connection, WIDTH, HEIGHT);
// 	if (NULL == fractol->img.img_ptr)
// 	{
// 		mlx_destroy_window(fractol->mlx_connection, fractol->mlx_window);
// 		mlx_destroy_display(fractol->mlx_connection);
// 		free(fractol->mlx_connection);
// 		malloc_error();
// 	}
// 	fractol->img.pixwls_ptr = mlx_get_data_addr(fractol->img.img_ptr, &fractol->img.bpp, &fractol->img.line_length, &fractol->img.endian);
// 	// fractol->max_iter = 50;
// 	// fractol->zoom = 1.0f;
// 	// fractol->x_shift = 0.0f;
// 	// fractol->y_shift = 0.0f;
// 	// fractol->min.real = -2.0f;
// 	// fractol->min.img = -1.0f;
// 	// fractol->max.real = 1.0f;
// 	// fractol->max.img = 1.0f;
// 	// fractol->fractal = mandelbrot;
// }

int main(int ac, char **av)
{
	t_fractol fractol;
	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10)) || (ac == 4 && !ft_strncmp(av[1], "julia", 5)))
	{
		printf("%s\n", "good");
		fractol.name = av[1];
		fractol_init(&fractol);
		fractol_render(&fractol);
		mlx_loop(fractol.mlx_connection);
	}
	else
	{
		ft_putstr_fd(ERROR_MESSAGE, 1);
		printf("res = %d", ft_strncmp(av[1], "mandelbrot", 10));
		exit(EXIT_FAILURE);
	}
	
}