#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdint.h>
//# include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "./minilibx-linux/mlx.h"
//#include "./minilibx-linux/mlx_int.h"
#include "./libft/libft.h"

#define ERROR_MESSAGE "please enter correct input\n"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define ZOOM 1.1f
# define THREADS 8

typedef struct s_complex
{
	double real;
	double img;
}t_complex;

#endif 