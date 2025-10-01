#!/bin/bash



#gcc -Wall -Wextra -Werror -g -I../include -I/home/kemzouri/minilibx-linux test.c -L/home/kemzouri/minilibx-linux -lmlx_Linux -lXext -lX11 -lm -o test 
#./test




 gcc -Wall -Wextra -Werror -g -I../include -I/home/kemzouri/minilibx-linux map2d_view.c -L/home/kemzouri/minilibx-linux -lmlx_Linux -lXext -lX11 -lm -o map2d_view
 ./map2d_view