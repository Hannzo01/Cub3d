int mouse_move(int x, int y, t_game *game)
{
    (void)y;
    int center_x;
    int center_y;
    int diff_x;
    
    center_x = SCREEN_W / 2;
    center_y = SCREEN_H / 2;
    diff_x = x - center_x;

    if (diff_x != 0)
    {
        rotate_player(game, diff_x * 0.0002);
        mlx_mouse_move(game->mlx, game->win, center_x, center_y);
    }
    return 0;
}