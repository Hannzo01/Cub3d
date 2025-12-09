/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:38:06 by kemzouri          #+#    #+#             */
/*   Updated: 2025/12/09 17:09:06 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../gnl/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"


//**********MACROS**************//

# define SCREEN_W 1080
# define SCREEN_H 720
# define TILE_SIZE 64

// Key codes
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define PLAYER_SIZE 8


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

//**********-STRUCTS-**************//
// ------PARSING--PART-------------//
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


// ------RAYCASTING--PART-------------//

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
}   t_player;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_maps
{
    char    **layout;
    int     width;
    int     height;
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    int     *floor_color;
    int     *ceil_color;
}   t_maps;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_img       screen;
    t_maps      map;
    t_player    player;
}   t_game;

typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     side;
}   t_ray;


//*******************************************************************//
//*************-FUNCTIONS-*************//
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
//*******************************************************************//

//***************************************//

//-------------RAYCASTING---------------//
// Algorithm functions
void    algorithm(t_map *data);
t_game  *fill_data(t_map *data);

// Raycasting
void    cast_ray(t_game *game, int x);
void    perform_dda(t_game *game, t_ray *ray);

// Rendering
int     render_map(t_game *game);
void    draw_wall(t_game *game, t_ray *ray, int x);
void    put_pixel(t_img *img, int x, int y, int color);

// Player
int     player_movment(int keycode, void *param);
void    move_player(t_game *game, double move_x, double move_y);
void    rotate_player(t_game *game, double angle);

// Helpers (if needed for linking)
void    *gc_malloc(int size, t_map *game);
void	*ft_memset(void *s, int c, size_t n);
//***************************************//

#endif