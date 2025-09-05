NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
SRCS = main.c parsing/check_file_name.c parsing/utils.c \
			parsing/lst_utils.c parsing/map_utils.c \
			gnll/get_next_line.c gnll/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re