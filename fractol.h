/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreron <7353718@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:38:08 by smoreron          #+#    #+#             */
/*   Updated: 2024/03/05 18:38:08 by smoreron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include <stdint.h>
//#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "libft/libft.h" 
#include "mlx_linux/mlx.h"

#define ERROR_MESSAGE "Please enter correct input\n"

#define WIDTH 800
#define HEIGHT 800

#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define GREEN 0x00FF00	
#define BLUE 0x0000FF	
#define YELLOW 0xFFFF00
#define CYAN 0x00FFFF
#define MAGENTA_BURST 0xFF00FF
#define LIME_SHOCK 0x00FF00
#define ORANGE 0xFFA500
#define NEON_ORANGE 0xFF5F00
#define PSYCHEDELIC_PURPLE 0x8A2BE2
#define AQUA_DREAM 0x7FFFD4
#define LIME_GREEN 0x32CD32
#define HOT_PINK 0xFF69B4
#define ELECTRIC_BLUE 0x7DF9FF
#define LAVA_RED 0xFF4500

typedef struct	s_complex
{
    double	x;
	//real
    double	y;
	//imaginary
}	t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixwls_ptr;
	int		bpp;
	int		endian;
	int		line_length;
} t_img;

typedef struct s_fractol
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	double	escape_value;
	int		iterations_defintion;

	// int bits_per_pixel;
	// int line_length;
	// int endian;
	// int max_iter;
	// double zoom;
	// double x_shift;
	// double y_shift;
	// t_complex c;
	// t_complex min;
	// t_complex max;
	// int (*fractal)(struct s_fractol *fractol, int x, int y);
} t_fractol;


// function prototypes
void		fractol_init(t_fractol *fractol);
void		fractol_render(t_fractol *fractol);
double		map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex	square_complex(t_complex z);
t_complex	sum_comlex(t_complex z1, t_complex z2);
double		escape_value(t_complex z);
static void	handle_pixel(int x, int y, t_fractol *fractol);
static void	malloc_error(void);
void		data_init(t_fractol *fractol);
static void	my_pixel_put(int x, int y, t_img *img, int color);

#endif