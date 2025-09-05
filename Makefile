CC = cc 
CFLAGS = -Wall -Wextra -Werror

FRAMEWORKS = -L/home/sechlahb/Desktop/minilibx-linux -lmlx -lX11 -lXext 


FILES = cub3d.c

OBJ = $(FILES:.c=.o)


NAME = cub3d



all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) -I/home/sechlahb/Desktop/minilibx-linux $(OBJ)  $(FRAMEWORKS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
