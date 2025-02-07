/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:49:18 by asalmi            #+#    #+#             */
/*   Updated: 2025/01/20 22:04:06 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void init_horizontal_intersection(t_game *game, double angle)
{
	game->horizontal.foundHorzWall = false;
	game->horizontal.horzWallHitX = 0;
	game->horizontal.horzWallHitY = 0;
	game->horizontal.y_intercept = floor(game->player.position_y / UNIT_SIZE) * UNIT_SIZE;
	if (is_facing_down(angle))
		game->horizontal.y_intercept += UNIT_SIZE;
	game->horizontal.x_intercept = ((game->horizontal.y_intercept - game->player.position_y) / tan(angle)) + game->player.position_x;
	game->horizontal.y_step = UNIT_SIZE;
	if (is_facing_up(angle))
		game->horizontal.y_step *= -1;
	game->horizontal.x_step = UNIT_SIZE / tan(angle);
	if (is_facing_left(angle) && game->horizontal.x_step > 0)
		game->horizontal.x_step *= -1;
	else if (is_facing_right(angle) && game->horizontal.x_step < 0)
		game->horizontal.x_step *= -1;
}

void horizontal_intersection(t_game *game, double angle)
{
	init_horizontal_intersection(game, angle);
	double nextHorzStepX = game->horizontal.x_intercept;
	double nextHorzStepY = game->horizontal.y_intercept;
	double checkStepX = 0;
	double checkStepY = 0;
	while (nextHorzStepX >= 0 && nextHorzStepX <= game->width * UNIT_SIZE 
		&& nextHorzStepY >= 0 && nextHorzStepY <= game->height * UNIT_SIZE)
	{
		checkStepX = nextHorzStepX;
		checkStepY = nextHorzStepY;
		if (is_facing_up(angle))
			checkStepY -= 1;
		if (is_wall(game, checkStepX, checkStepY))
		{
			game->horizontal.horzWallHitX = nextHorzStepX;
			game->horizontal.horzWallHitY = nextHorzStepY;
			game->horizontal.foundHorzWall = true;
			break;
		}
		nextHorzStepX += game->horizontal.x_step;
		nextHorzStepY += game->horizontal.y_step;
	
	}
}

void init_vertical_intersection(t_game *game, double angle)
{
	game->vertical.foundVertWall = false;
	game->vertical.vertWallHitX = 0;
	game->vertical.vertWallHitY = 0;
	game->vertical.x_intercept = floor(game->player.position_x / UNIT_SIZE) * UNIT_SIZE;
	if (is_facing_right(angle))
		game->vertical.x_intercept += UNIT_SIZE;
	game->vertical.y_intercept = game->player.position_y + (game->vertical.x_intercept - game->player.position_x) * tan(angle);
	game->vertical.x_step = UNIT_SIZE;
	if (is_facing_left(angle))
		game->vertical.x_step *= -1;
	game->vertical.y_step = UNIT_SIZE * tan(angle);
	if (is_facing_up(angle) && game->vertical.y_step > 0)
		game->vertical.y_step *= -1;
	else if (is_facing_down(angle) && game->vertical.y_step < 0)
		game->vertical.y_step *= -1;
}

void vertical_intersection(t_game *game, double angle)
{
	init_vertical_intersection(game, angle);
	double nextVertStepX = game->vertical.x_intercept;
	double nextVertStepY = game->vertical.y_intercept;
	double checkStepX = 0;
	double checkStepY = 0;
	while (nextVertStepX >= 0 && nextVertStepX <= game->width * UNIT_SIZE
			&& nextVertStepY >= 0 && nextVertStepY <= game->height * UNIT_SIZE)
	{
		checkStepX = nextVertStepX;
		if (is_facing_left(angle))
			checkStepX -= 1;
		checkStepY = nextVertStepY;
		if (is_wall(game, checkStepX, checkStepY))
		{
			game->vertical.vertWallHitX = nextVertStepX;
			game->vertical.vertWallHitY = nextVertStepY;
			game->vertical.foundVertWall = true;
			break ;
		}
		nextVertStepX += game->vertical.x_step;
		nextVertStepY += game->vertical.y_step;
	}
}

void find_distance(t_game *game, t_ray *ray, double angle)
{
	double horizontal_distance;
	double vertical_distance;

	horizontal_distance = INT_MAX;
	vertical_distance = INT_MAX;
	horizontal_intersection(game, angle);
	vertical_intersection(game, angle);
	if (game->horizontal.foundHorzWall)
		horizontal_distance = calculate_distance(game->player.position_x, game->player.position_y, game->horizontal.horzWallHitX, game->horizontal.horzWallHitY);
	if (game->vertical.foundVertWall)
		vertical_distance = calculate_distance(game->player.position_x, game->player.position_y, game->vertical.vertWallHitX, game->vertical.vertWallHitY);
	if (horizontal_distance < vertical_distance)
	{
		ray->wallHitX = game->horizontal.horzWallHitX;
		ray->wallHitY = game->horizontal.horzWallHitY;
		ray->distance = horizontal_distance;
		ray->foundHorz = true;
		ray->foundVert = false;
	}
	else
	{
		ray->wallHitX = game->vertical.vertWallHitX;
		ray->wallHitY = game->vertical.vertWallHitY;
		ray->distance = vertical_distance;
		ray->foundVert = true;
		ray->foundHorz = false;
	}
	ray->distance *= cos(game->player.angle_rotation - angle);
}

void cast_rays(t_game *game)
{
	int i;
	double angle;
	
	i = 0;
	game->rays->ray_angle = game->player.angle_rotation - (FOV / 2);
	while (i < game->rays_number)
	{
		angle = normalize_angle(game->rays->ray_angle);
		find_distance(game, &game->rays[i], angle);
		game->rays->ray_angle += (FOV / game->rays_number);
		i++;
	}
	i = 0;
	render_wall(game, game->rays);
	// while (i < game->rays_number)
	// {
	// 	// draw_line(game, game->rays[i]);
	// 	dda_test(game, game->rays[i]);
	// 	i++;
	// }
}
