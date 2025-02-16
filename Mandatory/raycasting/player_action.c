/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:11:16 by asalmi            #+#    #+#             */
/*   Updated: 2025/02/17 01:00:22 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void rotate_right(t_game *game)
{
	game->player.rotate_direction = 1;
	game->player.angle_rotation += game->player.rotate_direction * game->player.rotate_speed;
	game->player.angle_rotation = normalize_angle(game->player.angle_rotation);
}

void rotate_left(t_game *game) 
{
	game->player.rotate_direction = -1;
	game->player.angle_rotation += game->player.rotate_direction * game->player.rotate_speed;
	game->player.angle_rotation = normalize_angle(game->player.angle_rotation);
}

void open_door(t_game *game)
{
	int i;
	int midd_index;
	int grid_x;
	int grid_y;
	double distance;
	t_ray *midd_ray;
	
	midd_index = game->rays_number / 2;
	midd_ray = &game->rays[midd_index];
	distance = calculate_distance(game->player.position_x, game->player.position_y, midd_ray->wallHitX, midd_ray->wallHitY);
	// printf("open: %f\n", distance);
	grid_x = (int)(midd_ray->wallHitX / UNIT_SIZE);
	grid_y = (int)(midd_ray->wallHitY / UNIT_SIZE);
	if ((midd_ray->foundVertDoor || midd_ray->foundHorzDoor) && distance <= 65)
	{
		i = 0;
		// printf("----> x: %d ----> y: %d\n", grid_x, grid_y);
		while (i < doors_counter(game))
		{
			if (grid_x == game->doors[i].x && grid_y == game->doors[i].y && game->doors[i].is_closed)
			{
				game->map[grid_y][grid_x] = 'O';
				game->doors[i].is_closed = false;
				break;
			}
			i++;
		}
	}
}

int check_for_open(t_game *game, int door_x, int door_y)
{
    int player_x = floor(game->player.position_x / UNIT_SIZE);
    int player_y = floor(game->player.position_y / UNIT_SIZE);
	if (abs(door_x - player_x) <= 2 && abs(door_y - player_y) <= 2)
		return (1);
    return (0);
}

void close_door(t_game *game)
{
    int i = 0;
    int midd_index;
    t_ray *midd_ray;
	double dis_h;
	double dis_v;
    midd_index = game->rays_number / 2;
    midd_ray = &game->rays[midd_index];
    find_distance(game, midd_ray, game->player.angle_rotation);
	if (midd_ray->openVertDoor 
		&& check_for_open(game, midd_ray->v_openX, midd_ray->v_openY))
	{
        while (i < doors_counter(game))
        {
            if (game->doors[i].x == midd_ray->v_openX && game->doors[i].y == midd_ray->v_openY)
            {
                game->map[midd_ray->v_openY][midd_ray->v_openX] = 'C';
                game->doors[i].is_closed = true;
            }
            i++;
        }
	}
    i = 0;
	if (midd_ray->openHorzDoor
		&& check_for_open(game, midd_ray->h_openX, midd_ray->h_openY))
	{
        while (i < doors_counter(game))
        {
            if (game->doors[i].x == midd_ray->h_openX && game->doors[i].y == midd_ray->h_openY)
            {
                game->map[midd_ray->h_openY][midd_ray->h_openX] = 'C';
                game->doors[i].is_closed = true;
                break;
            }
            i++;
    	}	
	}
}

void movement_hook1(mlx_key_data_t key, void *param)
{
	t_game *game;
	
	game = param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	else if (key.key == MLX_KEY_RIGHT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		rotate_right(game);
	else if (key.key == MLX_KEY_LEFT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		rotate_left(game);
	else if (key.key == MLX_KEY_D && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		right_move(game);
	else if (key.key == MLX_KEY_A && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		left_move(game);
	else if (key.key == MLX_KEY_S && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		backward_move(game);
	else if (key.key == MLX_KEY_W && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		forward_move(game);
	else if (key.key == MLX_KEY_F && key.action == MLX_PRESS)
		open_door(game);
	else if (key.key == MLX_KEY_C && key.action == MLX_PRESS)
		close_door(game);
	game->player.rotate_direction = 0;
	game->player.move_direction = 0;
	rebuild_game(game);
}

void movement_hook(void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		right_move(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		left_move(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		backward_move(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		forward_move(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_F))
		open_door(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_C))
		close_door(game);
	game->player.rotate_direction = 0;
	game->player.move_direction = 0;
	rebuild_game(game);
}
