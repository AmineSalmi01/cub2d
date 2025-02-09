/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:58:06 by asalmi            #+#    #+#             */
/*   Updated: 2025/01/29 18:29:32 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void minimap_line(t_game *game, double px, double py)
{
	int i;
	double dx;
	double dy;
	double steps;
	double x_inc;
	double y_inc;
	double x1;
	double y1;

	i = -1;
	x1 = px + (12 * cos(game->player.angle_rotation));
	y1 = py + (12 * sin(game->player.angle_rotation));
	dx = x1 - px;
	dy = y1 - py;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else	
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	while (++i <= steps)
	{
		mlx_put_pixel(game->minimap_img, round(px), round(py), rgbt_color(155, 77, 214, 255));
		if (px < 0 || py < 0 || px >= game->minimap_width || py >= game->minimap_width)
            break;
		px += x_inc;
		py += y_inc;
	}
}

void minimap_player(t_game *game)
{
	double px;
	double py;
	int x1;
	int y1;
	int i;
	int j;

	px = game->minimap_width / 2;
	py = game->minimap_height / 2;
	
	i = -3;
	j = -3;
	while (i < 3)
	{
		j = -3;
		while (j < 3)
		{
			mlx_put_pixel(game->minimap_img, px + j, py + i, rgbt_color(155, 77, 214, 255));
			j++;
		}
		i++;
	}
	minimap_line(game, px, py);
}

int check_for_draw(t_game *game, int x, int y)
{
	double px;
	double py;
	int xd;
	int yd;

	px = game->minimap_width / 2;
	py = game->minimap_height / 2;
	xd = (x - px) / ZOOM;
	yd = (y - py) / ZOOM;
	xd = (game->player.position_x) + xd;
	yd = (game->player.position_y) + yd;
	if (xd < 0 || yd < 0)
		return (-1);
	if (yd >= game->height * UNIT_SIZE)
		return (-1);
	xd /= UNIT_SIZE;
	yd /= UNIT_SIZE;
	if (xd >= ft_strlen(game->map[yd]))
		return (-1);
	if (game->map[yd][xd] == 10)
		return (-1);
	if (game->map[yd][xd] == '1')
		return (1);
	if (game->map[yd][xd] == 32)
		return (1);
	if (game->map[yd][xd] == 'C')
		return (2);
	if (game->map[yd][xd] == 'O')
		return (3);
	return (0);
}

void darw_object(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	int status; 
	while (y < game->minimap_height)
	{
		x = 0;
		while (x < game->minimap_width)
		{
			status = check_for_draw(game, x, y);
			if (status == 0)
				mlx_put_pixel(game->minimap_img, x, y, rgbt_color(255, 255, 255, 255));
			if (status == 1)
				mlx_put_pixel(game->minimap_img, x, y, rgbt_color(27, 27, 27, 255));
			if (status == -1)
				mlx_put_pixel(game->minimap_img, x, y, rgbt_color(67, 67, 67, 255));
			if (status == 2)
				mlx_put_pixel(game->minimap_img, x, y, rgbt_color(107, 229, 184, 255));
			if (status == 3)
				mlx_put_pixel(game->minimap_img, x, y, rgbt_color(204, 204, 255, 255));
			x++;
		}
		y++;
	}
}

void draw_minimap(t_game *game)
{
	game->minimap_width = 7 * UNIT_SIZE;
	game->minimap_height = 5 * UNIT_SIZE;
	int i;
	int j;
	
	i = 0;
	j = 0;
	game->minimap_img = mlx_new_image(game->mlx, game->minimap_width, game->minimap_height);
	if ((!game->minimap_img) || (mlx_image_to_window(game->mlx, game->minimap_img, 10, 10)) < 0)
		return ;
	darw_object(game);
	minimap_player(game);
}
