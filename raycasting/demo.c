#include <cub3d.h>
#include <string.h>


// i need a clean 2d array grid 
// start mlx , create window , render pixel
// having a smooth 2d arat

#define COLS 11 //x width
#define ROWS 11   //y	height
#define TILE_SIZE 32
#define CELL_SIZE 32
#define PI 3.14159265359
#define PLANE_LENGTH 0.66


typedef struct s_player
{
	//player position
	double px;
	double py;

	//direction vector = where the player is looking
	double dirx;
	double diry;

	//camera plane = perpendicular to direction, defines the field of view.

	double planex;
	double planey;
	
	float camerax;
	double raydirx;
	double raydiry;

}	t_player;

typedef struct s_grid
{
	char **map;


	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_image;
	
	t_player *player;

	char	*address;
	int		endian;
	int 	bits_per_pixel;
	int		length_line;
}	t_grid;



void map_copy(t_grid *grid, char *map[])
{
	grid->map = malloc(sizeof(char *) * 11);
	for (int i = 0 ; i < 11; i++)
	{
		grid->map[i] = strdup(map[i]);
	}
	
	// Allocate memory for player structure
	grid->player = malloc(sizeof(t_player));
	
	grid->player->px = 5 + 0.5;  //+0.5 to puts the player in the center of the cell
	grid->player->py = 3 + 0.5;

	grid->player->dirx = 0;  //player looking up 
	grid->player->diry = -1;

	grid->player->planex = -grid->player->diry * PLANE_LENGTH;
	grid->player->planey = grid->player->dirx * PLANE_LENGTH;

	grid->player->camerax = 2 * grid->player->dirx / COLS - 1;

	grid->player->raydirx = grid->player->dirx + grid->player->planex * grid->player->camerax;
	grid->player->raydiry = grid->player->diry + grid->player->planey * grid->player->camerax;


}
int ft_close(t_grid *grid)
{	
	(void)grid;
	exit(1);
}

void	put_pixel(t_grid *grid, int x_pixel, int y_pixel, int color)
{
	int offset = (y_pixel * grid->length_line + x_pixel * (grid->bits_per_pixel / 8));
	*(unsigned int *)(grid->address + offset) = color;
}

void	draw_circle(t_grid *grid, int cx, int cy, int radius, int color)
{
	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			if (x*x + y*y <= radius*radius)
				put_pixel(grid, cx + x, cy + y, color);
		}
	}
}

void	render_one_cell(t_grid *grid, int color, int x, int y)
{
	int x_pixel;
	int y_pixel;

	int x_pixel_start = x * CELL_SIZE;
	int	y_pixel_start = y * CELL_SIZE;


	y_pixel = y_pixel_start;
	while (y_pixel < y_pixel_start + CELL_SIZE)
	{
		x_pixel = x_pixel_start;
		while (x_pixel < x_pixel_start + CELL_SIZE)
		{
			put_pixel(grid, x_pixel, y_pixel, color);
			x_pixel++;
		}
		y_pixel++;
	}
}

void	render_pixels(t_grid *grid)
{
	for (int i = 0 ; i < 11; i++)
	{
		int j = 0;
		for (j = 0; j < 11; j++)
		{
			if (grid->map[i][j] == '1')
				render_one_cell(grid, 0x7F2222, j, i);
			else if (grid->map[i][j] == '0')
				render_one_cell(grid, 0xFFFFFF, j, i);
		}
	}
	
	// Draw player as a blue circle at manually set position
	int px_pixel = (int)(grid->player->px * CELL_SIZE);
	int py_pixel = (int)(grid->player->py * CELL_SIZE);
	draw_circle(grid, px_pixel, py_pixel, 5, 0x0000FF); // Blue circle with 5px radius
}

void	start_mlx(t_grid *grid)
{
	grid->mlx_ptr  = mlx_init();
	grid->mlx_win = mlx_new_window(grid->mlx_ptr, COLS * TILE_SIZE, ROWS * TILE_SIZE, "cub2d");
	grid->mlx_image = mlx_new_image(grid->mlx_ptr, COLS * TILE_SIZE, ROWS * TILE_SIZE);
	grid->address = mlx_get_data_addr(grid->mlx_image, &grid->bits_per_pixel, &grid->length_line, &grid->endian);


	render_pixels(grid);
	mlx_put_image_to_window(grid->mlx_ptr, grid->mlx_win ,grid->mlx_image, 0, 0);

	mlx_hook(grid->mlx_win, 17 ,0, ft_close, grid);
	mlx_loop(grid->mlx_ptr);
}

int main()
{
	t_grid *grid = malloc(sizeof(t_grid));
	char *map[] = {"11111111111",
					"10001001011",
					"10010000101",
					"11110000011",
					"10000000001",
					"10001000001",
					"11000010001",
					"10000010011",
					"11000010001",
					"10110000011",
					"11111111111"};
	map_copy(grid ,map);
	start_mlx(grid);
}
