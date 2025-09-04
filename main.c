#include "include/cub3d.h"
#include  <string.h>


int main(int argc, char *argv[])
{
	t_list *lst;
	t_map *game;

	lst = NULL;
	game = malloc(sizeof(t_map));
	if (game == NULL)
		return (1);

	if (argc == 2)
	{
		if (check_file_name(argv[1]) == 1)
			return (ft_putstr_fd("Invalid file name\n", 2), 1);
		read_map(argv[1], &lst); 
		map_size(lst, game); //need to free linked list
		allocate_and_fill_map(game, lst);
		print_map(game->map);
	}
	else
		return (ft_putstr_fd("Enter a valid input :)\n", 2), 1);
	return (0);
}
