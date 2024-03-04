NAME = fractol
CC = gcc
CFLAGS =  -I/usr/include -Imlx_linux -O3 #-Wextra -Werror -Wall 
SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)
LIBS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
