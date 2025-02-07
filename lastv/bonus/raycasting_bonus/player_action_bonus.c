/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:11:16 by asalmi            #+#    #+#             */
/*   Updated: 2025/01/20 22:03:56 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void key_hook(mlx_key_data_t key, void *param)
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
	game->player.rotate_direction = 0;
	game->player.move_direction = 0;
	rebuild_game(game);
}
