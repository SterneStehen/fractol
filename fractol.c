# include "fractol.h"



int ft_fractal()
{
	double tmp_real;
	t_complex z;
	t_complex c;
	z.real = 0;
	z.img = 0;
	c.real = 5;
	c.img = 2;
	for (size_t i = 0; i < 42; i++)
	{
		//f(z) = z^2 + c;
		tmp_real = (z.real* z.real) - (z.img* z.img);
		z.img = 2 * z.real * z.img;
		z.real = tmp_real;
		z.real += c.real;
		z.img += c.img;
		printf("iteration n -> %ld real %.2f imeginary %.2f\n", i, z.real, z.img);
	}
	

}
