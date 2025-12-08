NAME = cub3d
BONUS_NAME = cub3d_bonus

CC = gcc
CFLAGS = -g -I./minilibx-linux -I./include  -Wall -Wextra -Werror
BONUS_CFLAGS = -g -I./bonus/minilibx-linux -I./bonus/include  -Wall -Wextra -Werror

SRCS = cub3d.c \
		parsing/check_file_name.c parsing/utils.c parsing/utils_II.c \
		parsing/lst_utils.c parsing/split.c parsing/flood_fill.c \
		parsing/init_struct.c parsing/check_map_contents.c \
		parsing/validate_map.c parsing/clean_and_exit.c \
		parsing/read_and_storemap.c parsing/textures_parser.c \
		parsing/colors_parser.c parsing/map_state.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c \
		algorithm/algorithm.c algorithm/player.c algorithm/raycasting.c \
		algorithm/rendering.c algorithm/utils.c

BONUS_SRCS = bonus/cub3d_bonus.c \
		bonus/parsing/check_file_name_bonus.c bonus/parsing/utils_bonus.c bonus/parsing/utils_II_bonus.c \
		bonus/parsing/lst_utils_bonus.c bonus/parsing/split_bonus.c bonus/parsing/flood_fill_bonus.c \
		bonus/parsing/init_struct_bonus.c bonus/parsing/check_map_contents_bonus.c \
		bonus/parsing/validate_map_bonus.c bonus/parsing/clean_and_exit_bonus.c \
		bonus/parsing/read_and_storemap_bonus.c bonus/parsing/textures_parser_bonus.c \
		bonus/parsing/colors_parser_bonus.c bonus/parsing/map_state_bonus.c \
		bonus/gnl/get_next_line_bonus.c bonus/gnl/get_next_line_utils_bonus.c \
		bonus/algorithm/algorithm_bonus.c bonus/algorithm/player_bonus.c bonus/algorithm/raycasting_bonus.c \
		bonus/algorithm/rendering_bonus.c bonus/algorithm/utils_bonus.c bonus/algorithm/mini_map_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) ./minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(BONUS_CFLAGS) $(BONUS_OBJS) ./bonus/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm -o $(BONUS_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY : all bonus clean fclean re