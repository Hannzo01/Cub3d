NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #remove
SRCS = main.c parsing/check_file_name.c parsing/utils.c \
			parsing/lst_utils.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c \
			parsing/split.c parsing/flood_fill.c parsing/init_struct.c \
			parsing/check_map_contents.c parsing/validate_map.c \
			parsing/utils_II.c parsing/clean_and_exit.c \
			parsing/read_and_storemap.c parsing/textures_parser.c \
			parsing/colors_parser.c parsing/map_state.c


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