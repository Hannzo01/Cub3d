
#include <cub3d.h>

typedef struct s_game
{
	char	**map;
	int		px;
	int		py;
	int		player_pixel_x; //player pixel position
	int		player_pixel_y;
	int		map_height;
	int		map_width;
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_image;
	char	*address; //start of image memory.
	int		bits_p_pixel;
	int		length_line;
	int		endian;
	int		cell_size;
}	t_game;	



// how far from the start of address the pixel (x, y) is
void	put_pixel(t_game *game, int color, int pixel_x, int pixel_y)
{
	int	offset = (pixel_y * game->length_line + pixel_x * (game->bits_p_pixel / 8));
	*(unsigned int *)(game->address + offset) = color;
}

int	decide_colors(int y, int x, t_game *game)
{
	if (game->map[y][x] == '1')
		return (0xabcd96);
	else if (game->map[y][x] == '0')
		return (0xad8ba2);
	else if (game->map[y][x] == 'P')
		return (0xa83886);
	else
		return (0xc0cf63);
}

void	fill_one_cell(t_game *game, int rows, int col, int color)
{
	int	pixel_x_start = col * 64;
	int	pixel_y_start = rows * 64;
	int pixel_x;
	int pixel_y;
	
	pixel_y = pixel_y_start;
	while (pixel_y < pixel_y_start + game->cell_size)
	{
		pixel_x = pixel_x_start;
		while (pixel_x < pixel_x_start + game->cell_size)
		{
			if (game->map[rows][col] == 'P')
			{
				if (pixel_x == pixel_x_start || pixel_x == pixel_x_start + game->cell_size -1 \
						|| pixel_y == pixel_y_start || pixel_y == pixel_y_start + game->cell_size - 1)
					put_pixel(game, 0xffffff, pixel_x, pixel_y);
				else if (pixel_y <= pixel_y_start + 18 || pixel_y >= pixel_y_start + 45 || 
						pixel_x <= pixel_x_start + 18 || pixel_x >= pixel_x_start + 45 )
					put_pixel(game, 0xad8ba2, pixel_x, pixel_y);
				else
					put_pixel(game, 0x290000, pixel_x, pixel_y);
			}
			if (game->map[rows][col] != 'P')
			{
				if (pixel_x == pixel_x_start || pixel_x == pixel_x_start + game->cell_size -1 \
						|| pixel_y == pixel_y_start || pixel_y == pixel_y_start + game->cell_size - 1)
					put_pixel(game, 0xffffff, pixel_x, pixel_y);
				else
					put_pixel(game, color, pixel_x, pixel_y);
			}
			pixel_x++;
		}
		pixel_y++;
	}

}

void	render_line(int col, int rows, t_game *game)
{
	//x and y : starting point of the line
		   //col = cord of the map Player cell
		   		  //64 pixels + 32 pixel center 
	int x = col * game->cell_size + game->cell_size / 2;
	int y = rows * game->cell_size  + game->cell_size / 2;
	while (game->map[y / game->cell_size][x / game->cell_size] != '1')
	{
		put_pixel(game, 0xff0000, x, y);
		x = x + 1;
	}

}

void	render_2d_map(t_game *game)
{
	int	rows;
	int	col;
	int color;

	rows = 0;
	while (rows < game->map_height)
	{
		col = 0;
		while (col < game->map_width)
		{
			color = decide_colors(rows, col, game);
			fill_one_cell(game, rows, col, color); //loop over all pixels inside one cell
			if (game->map[rows][col] == 'P')
				render_line(col, rows, game);
			col++;
		}
		rows++;
	}
}

int	ft_handler(int keypress, void *struc)
{
	t_game *game = (t_game *)struc;
	int new_x = game->px;
	int new_y = game->py;
	
	if (keypress == 65307)
		exit(1);
	else if (keypress == 119) //up
		new_y = game->py - 1;
	else if (keypress == 97)  //left
		new_x = game->px - 1;
	else if (keypress == 100) //right
		new_x = game->px + 1;
	else if	(keypress == 115) //down
		new_y = game->py + 1;
	
	if (game->map[new_y][new_x] != '1')
	{
		game->map[game->py][game->px] = '0';
		game->px = new_x;
		game->py = new_y;
		game->map[game->py][game->px] = 'P';
	}
	render_2d_map(game);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->mlx_image, game->map_width, game->map_height);
	return (0);
}

int	ft_close(t_game *game)
{
	(void)game;
	exit (0);
}
void	mlx_ini(t_game *game)
{
	game->mlx_ptr = mlx_init();                                 //each map cell is 64×64 pixels
	game->mlx_win = mlx_new_window(game->mlx_ptr, game->map_width * game->cell_size , game->map_height * game->cell_size, "First attempt");
	game->mlx_image = mlx_new_image(game->mlx_ptr, game->map_width * game->cell_size, game->map_height * game->cell_size);
	game->address = mlx_get_data_addr(game->mlx_image, &game->bits_p_pixel, &game->length_line, &game->endian);


	render_2d_map(game);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->mlx_image, 0, 0);
	
	
	
	mlx_hook(game->mlx_win, 17, 0, ft_close, game);  //17 for close window
	mlx_key_hook(game->mlx_win, ft_handler, game);
	mlx_loop(game->mlx_ptr);
	mlx_destroy_window(game->mlx_ptr, game->mlx_win);
}

void initiliaze_struct(t_game *game)
{
	//Each character = 1 cell
	//Each cell = 64×64 pixels
	static char *tmp_map[] = {
    "1111111",
    "1000001",
    "1010101",
    "100P001",
    "1010101",
    "1000001",
    "1111111"
	};
	memset(game, 0, sizeof(t_game));
	game->cell_size = 64;
	game->map_height = 7;
	game->map_width = 7;
	game->map = malloc(sizeof(char *) * (game->map_height));
	for (int i = 0; i < game->map_height; i++)
	{
		game->map[i] = malloc(game->map_width + 1);
		strcpy(game->map[i], tmp_map[i]);
	}
	
	for (int i = 0; i < game->map_height; i++)
	{
		for (int j = 0; j < game->map_width; j++)
		{
			if (game->map[i][j] == 'P')
			{
				game->px = j;
				game->py = i;
				break;
			}
		}
	}
}

void rendering(t_game *game)
{
	initiliaze_struct(game);
	mlx_ini(game);

	//draws the rays in 2d
	//draws walls and textures in 3d
}


int main()
{
	t_game *game = malloc(sizeof(t_game));
	rendering(game);
	
}
