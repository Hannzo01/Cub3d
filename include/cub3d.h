#ifndef CUB3D_H
#define CUB3D_H

# include "../gnl/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



typedef struct s_list
{
	char			*line;
	struct	s_list	*next;
}	t_list;

typedef struct s_map
{
	int		map_height;
	int		max_len;
	char	**map;
}	t_map;

typedef struct s_map_info
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		Floor[3];
	int		Ceiling[3];
	int		stop_trimming;
}	t_map_info;



//-------------PARSING---------------//
int		check_file_name(char *name);
void read_map(char *filename, t_list **lst, t_map_info *map_info);
void	allocate_and_fill_map(t_map *game, t_list *lst);
void	print_map(char **map); //remove later





//--------------UTILS----------------//
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strrchr(char *s, int c);
char	*ft_strcpy(char *dst, char *src);


void	lstadd_back(t_list **lst, char *line);
t_list	*lst_new(char *line);
void	print_list(t_list *lst);  //remove later
void	map_size(t_list *lst, t_map *game);


#endif