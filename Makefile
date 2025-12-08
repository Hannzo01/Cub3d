NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# MLX configuration
MLX_DIR = /home/sechlahb/Desktop/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC_DIR = algorithm
INC_DIR = include

# Algorithm sources
ALGO_SRCS = $(SRC_DIR)/algorithm.c \
			$(SRC_DIR)/raycasting.c \
			$(SRC_DIR)/rendering.c \
			$(SRC_DIR)/player.c \
			$(SRC_DIR)/helpers.c

# Automatically find all other .c files in the project
# Excludes algorithm folder (handled above) and minilibx folder
MAIN_SRCS = $(shell find . -type f -name "*.c" ! -path "./algorithm/*" ! -path "*/minilibx-linux/*" ! -path "./test/*")

SRCS = $(ALGO_SRCS) $(MAIN_SRCS)
OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR) >/dev/null 2>&1

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean >/dev/null 2>&1

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re