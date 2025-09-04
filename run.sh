#!/bin/bash
cc -Wall -Wextra -Werror \
-I/home/sechlahb/Desktop/minilibx-linux \
cub3d.c -o cub3d \
-L/home/sechlahb/Desktop/minilibx-linux \
-lmlx -lX11 -lXext -lm

# #!/bin/bash
# cc -Wall -Wextra -Werror \
# -I/home/sechlahb/Desktop/minilibx-linux \
# -L/home/sechlahb/Desktop/minilibx-linux \
# -lmlx -lX11 -lXext -lm \
# cub3d.c -o cub3d

# cc -Wall -Wextra -Werror  -L//home/sechlahb/Desktop/minilibx-linux -lmlx -lX11 -lXext \
# cub3d.c -o cub3d