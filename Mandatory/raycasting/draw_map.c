/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:41:32 by asalmi            #+#    #+#             */
/*   Updated: 2025/02/07 17:31:47 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_dda init_dda(t_game *game, t_ray ray)
{
	t_dda dd;

	dd.x0 = game->player.position_x;
	dd.y0 = game->player.position_y;
	dd.x1 = ray.wallHitX;
	dd.y1 = ray.wallHitY;
	dd.dx = abs(dd.x1 - dd.x0);
	dd.dy = abs(dd.y1 - dd.y0);
	if (dd.x0 < dd.x1)
	 	dd.stepx = 1;
	else
		dd.stepx = -1;
	if (dd.y0 < dd.y1)
		dd.stepy = 1;
	else
		dd.stepy = -1;
	dd.err = dd.dx - dd.dy;
	return (dd);
}

void dda_test(t_game *game, t_ray ray)
{	
	t_dda dd;
	dd = init_dda(game, ray);
	while (1)
	{
		if (dd.x0 < 0 || dd.y0 < 0 || dd.x0 >= (int)game->width * UNIT_SIZE || dd.y0 >= (int)game->height * UNIT_SIZE)
			return ;
		mlx_put_pixel(game->image, dd.x0, dd.y0, 0xFF0000ff);
		if (dd.x0 == dd.x1 && dd.y0 == dd.y1)
			break;
		dd.e2 = 2 * dd.err;
		if (dd.e2 > -dd.dy)
		{
			dd.err -= dd.dy;
			dd.x0 += dd.stepx;
		}
		if (dd.e2 < dd.dx)
		{
			dd.err += dd.dx;
			dd.y0 += dd.stepy;
		}
	}
}

void draw_line(t_game *game, t_ray ray)
{
	int i;
	double dx;
	double dy;
	double x0;
	double y0;
	double steps;
	double x_inc;
	double y_inc;
	double x1;
	double y1;

	i = -1;
	x1 = ray.wallHitX;
	y1 = ray.wallHitY;
	x0 = game->player.position_x;
	y0 = game->player.position_y;
	dx = x1 - x0;
	dy = y1 - y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	while (++i <= steps)
	{
		mlx_put_pixel(game->image, round(x0), round(y0), 0xFF0000ff);
		if (x0 < 0 || y0 < 0 || x0 >= game->width * UNIT_SIZE || y0 >= game->height * UNIT_SIZE)
            break;
		x0 += x_inc;
		y0 += y_inc;
	}
}

void draw_grid(t_game *game)
{
	size_t x;
	size_t y;
	
	for (y = 0; y < game->height * UNIT_SIZE; y += UNIT_SIZE)
	{
		for (x = 0; x < game->width * UNIT_SIZE; x++)
		{
			mlx_put_pixel(game->image, x, y, 0xb5b8b7);
		}
	}
	for (x = 0; x < game->width * UNIT_SIZE; x += UNIT_SIZE)
	{
		for (y = 0; y < game->height * UNIT_SIZE; y++)
		{
			mlx_put_pixel(game->image, x, y, 0xb5b8b7);
		}
	}
}
void render_wall(t_game *game, t_ray *ray)
{
	int i;
	int terp;
	
	terp = 0;
	i = 0;
	double projection_distance = (WIDTH / 2) / tan(FOV / 2);
	while (i < game->rays_number)
	{
		double p_wall_height = (UNIT_SIZE / ray[i].distance) * projection_distance;
		int walltopPixel = (HEIGHT / 2) - (p_wall_height / 2);
		if (walltopPixel < 0)
			walltopPixel = 0;
		int wallbuttomPixel = (HEIGHT / 2) + (p_wall_height / 2);
		if (wallbuttomPixel > HEIGHT)
			wallbuttomPixel = HEIGHT;
		int y = walltopPixel;
		terp = depth_color(ray[i].distance, terp);
		while (y < wallbuttomPixel)
		{
			if (ray[i].foundDoor)
				mlx_put_pixel(game->image, i, y, rgbt_color(107, 229, 184, terp));				
			else if (ray[i].foundHorz)
				mlx_put_pixel(game->image, i, y, rgbt_color(204, 26, 198, terp));
			else if (ray[i].foundVert)
				mlx_put_pixel(game->image, i, y, rgbt_color(143, 16, 139, terp));
			y++;
		}
		i++;
	}
}

void draw_background(t_game *game)
{
	size_t x;
	size_t y;

	x = 0;
	y = 0;
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if ((!game->image) || (mlx_image_to_window(game->mlx, game->image, 0, 0) < 0))
		return ;
	while (HEIGHT > y)
	{
		x = 0;
		while (WIDTH > x)
		{
			mlx_put_pixel(game->image, x, y, 0x33030);
			x++;	
		}
		y++;
	}
	// draw_grid(game);
}

void draw_doors(t_game *game)
{
	int x;
	int y;
	int i;
	int j;
	int position_x;
	int position_y;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	position_x = 0;
	position_y = 0;
	while (game->map[i])
	{
		j = 0;
		position_x = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'C')
			{
				y = 0;
				while (UNIT_SIZE > y)
				{
					x = 0;
					while (UNIT_SIZE > x)
					{
						mlx_put_pixel(game->image, x + position_x, y + position_y, rgbt_color(107, 229, 184, 255));
						x++;
					}
					y++;
				}
			}
			else if (game->map[i][j] == 'O')
			{
				y = 0;
				while (UNIT_SIZE > y)
				{
					x = 0;
					while (UNIT_SIZE > x)
					{
						mlx_put_pixel(game->image, x + position_x, y + position_y, rgbt_color(204, 204, 255, 255));
						x++;
					}
					y++;
				}
			}
			j++;
			position_x += UNIT_SIZE;	
		}
		i++;
		position_y += UNIT_SIZE;
	}
}

void draw_wall(t_game *game)
{
	int x;
	int y;
	int i;
	int j;
	int position_x;
	int position_y;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	position_x = 0;
	position_y = 0;
	while (game->map[i])
	{
		j = 0;
		position_x = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
			{
				y = 0;
				while (UNIT_SIZE > y)
				{
					x = 0;
					while (UNIT_SIZE > x)
					{
						mlx_put_pixel(game->image, x + position_x, y + position_y, 0x000000FF);
						x++;
					}
					y++;
				}
			}
			j++;
			position_x += UNIT_SIZE;	
		}
		i++;
		position_y += UNIT_SIZE;
	}
}

void draw_player(t_game *game)
{
	int x;
	int y;
	
	x = -5;
	y = -5;
	while (y < 5)
	{
		x = -5;
		while (x < 5)
		{
			mlx_put_pixel(game->image, game->player.position_x + x, game->player.position_y + y, 0xFF0000ff);
			x++;
		}
		y++;
	}
}
