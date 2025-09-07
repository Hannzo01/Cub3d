NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I/home/kemzouri/minilibx-linux
SRCS = cub3d.c parsing/check_file_name.c parsing/utils.c \
			parsing/lst_utils.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c \
			parsing/split.c parsing/flood_fill.c parsing/init_struct.c \
			parsing/check_map_contents.c parsing/validate_map.c \
			parsing/utils_II.c parsing/clean_and_exit.c \
			parsing/read_and_storemap.c parsing/textures_parser.c \
			parsing/colors_parser.c parsing/map_state.c \
			raycasting/map2d_view.c 


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) /home/kemzouri/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re