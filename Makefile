NAME = fractol
CC = gcc
CFLAGS = -I/usr/include -Imlx_linux -O3 #-Wextra -Werror -Wall 
SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)
LIBS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
LIBF = -Llibft -lft

all: libft_all $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(LIBF) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft_all:
	make -C libft

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft_all