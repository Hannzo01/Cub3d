NAME        = cub3d

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror

# --- PATHS ---
MLX_PATH    = /home/sechlahb/Desktop/minilibx-linux
# MLX_PATH    = /home/kemzouri/minilibx-linux

# MLX_PATH    = minilibx-linux

# Mandatory
MLX_LIB     = $(MLX_PATH)/libmlx_Linux.a
MLX_FLAGS   = -lXext -lX11 -lm


# --- SOURCES ---
SRCS = cub3d.c \
        parsing/check_file_name.c parsing/utils.c parsing/utils_II.c \
        parsing/lst_utils.c parsing/split.c parsing/flood_fill.c \
        parsing/init_struct.c parsing/check_map_contents.c \
        parsing/validate_map.c parsing/clean_and_exit.c \
        parsing/read_and_storemap.c parsing/textures_parser.c \
        parsing/colors_parser.c parsing/map_state.c \
        gnl/get_next_line.c gnl/get_next_line_utils.c \
        algorithm/algorithm.c algorithm/player.c algorithm/raycasting.c \
        algorithm/init_textures.c algorithm/tools00.c algorithm/pixels.c \
         algorithm/draw_wall.c algorithm/dda.c algorithm/delete.c


OBJS        = $(SRCS:.c=.o)

# --- RULES ---
all: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY : all  clean fclean re