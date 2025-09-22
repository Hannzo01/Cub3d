/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:38:06 by kemzouri          #+#    #+#             */
/*   Updated: 2025/09/21 22:26:43 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../gnl/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "cub3d2.h"

typedef struct s_gc
{
	struct s_gc		*next;
	void			*p;
}					t_gc;

typedef struct s_list
{
	char			*line;
	struct s_list	*next;
}					t_list;

typedef struct s_info
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f[3];
	int				c[3];
	int				is_full;
}					t_info;

typedef struct s_map
{
	t_info			*map_info;
	int				height;
	int				max_len;
	char			**map;
	char			**clone_map;
	int				p_found;
	int				p_x;
	int				p_y;
	int				invalid;
	t_gc			*gc;
}					t_map;

//-------------PARSING---------------//
void				check_file_name(char *name, t_map *game);
void				allocate_and_fill_map(t_map *game, t_list *lst);
void				read_map(char *filename, t_list **lst, t_map *game);
void				copy_map(t_map *game);
void				initialize_game(t_map *game);
void				flood_fill(t_map *game, int x, int y);
int					valid_chars(t_map *game);
int					is_surrounded(t_map *game);
int					is_wall(char *str);
int					is_valid_line(char *str, t_map *game);
void				validate_map(t_map *game);
void				save_player_pos(t_map *game);
void				*gc_malloc(int size, t_map *game);

void				allocate_and_fill_map(t_map *game, t_list *lst);

void				is_fully_filled(t_map *game);
void				are_floor_and_ceiling_diff(t_map *game);
void				check_if_metabeta(char *line, t_map *game);
int					count_param(char *line);
void				validate_and_fill_texture(char *element, char *line,
						t_map *game);
void				print_error_and_exit(char *msg, t_map *game);
char				*elemet_value(char *line, t_map *game);
void				check_and_fill_color(char *element, char *tab, t_map *game);
char				*elemet_var(char *line, t_map *game);
int					check_for_empty_line(char *str);

//--------------UTILS----------------//
void				ft_putstr_fd(char *s, int fd);
int					ft_strlen(char *s);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strrchr(char *s, int c);
char				*ft_strcpy(char *dst, char *src);
char				**ft_split(char *s, char c, t_map *game);
int					ft_atoi(char *nptr);
char				*ft_substr(char *s, int start, int len, t_map *game);
int					ft_strncmp(char *s1, char *s2, int n);
char				*f_strdup(char *str, t_map *game);
void				gc_free(t_gc *gc);

void				lstadd_back(t_list **lst, char *line, t_map *game);
t_list				*lst_new(char *line, t_map *game);
void				map_size(t_list *lst, t_map *game);

//----REMOVE---->>>DEBUGGING------//

// void	debug_map_validation(t_map *game);
// int		validate_map(t_map *game);
// void	print_map(char **map);

void algorithm(t_map *game);
int player_movment(int key, void *game);
int   rander_map(t_game *game);
/*tools*/
void	*ft_memset(void *s, int c, size_t n);
#endif