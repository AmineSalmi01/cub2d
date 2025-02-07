/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:24:27 by asalmi            #+#    #+#             */
/*   Updated: 2025/01/27 21:41:00 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int check_map(t_game *game, double new_position_x, double new_position_y)
{
	int i;
	int tmp_x;
	int tmp_y;
	
	i = -MOVE_SPEED;
	tmp_x = floor(new_position_x);
	tmp_y = floor(new_position_y);
	while (i <= MOVE_SPEED)
	{
		if (game->map[(tmp_y + i) / UNIT_SIZE][tmp_x / UNIT_SIZE] == '1' 
			|| game->map[(tmp_y + i) / UNIT_SIZE][tmp_x / UNIT_SIZE] == 'C')
			return (0);
		i++;
	}
	i = -MOVE_SPEED;
	while (i <= MOVE_SPEED)
	{
		if (game->map[tmp_y / UNIT_SIZE][(tmp_x + i) / UNIT_SIZE] == '1'
			|| game->map[(tmp_y + i) / UNIT_SIZE][tmp_x / UNIT_SIZE] == 'C')
			return (0);
		i++;
	}
	return (1);
}

void right_move(t_game *game)
{
	double move_steps;
	double new_position_x;
	double new_position_y;

	move_steps = game->player.move_speed;
	new_position_x = game->player.position_x;
	new_position_y = game->player.position_y;
	new_position_x += cos(game->player.angle_rotation + M_PI / 2) * move_steps;
	new_position_y += sin(game->player.angle_rotation + M_PI / 2) * move_steps;
	if (!check_map(game, new_position_x, new_position_y))
		return ;
	game->player.position_x = new_position_x;
	game->player.position_y = new_position_y;
}

void left_move(t_game *game)
{
	double move_steps;
	double new_position_x;
	double new_position_y;

	move_steps = game->player.move_speed;
	new_position_x = game->player.position_x;
	new_position_y = game->player.position_y;
	new_position_x -= cos(game->player.angle_rotation + M_PI / 2) * move_steps;
	new_position_y -= sin(game->player.angle_rotation + M_PI / 2) * move_steps;
	if (!check_map(game, new_position_x, new_position_y))
		return ;
	game->player.position_x = new_position_x;
	game->player.position_y = new_position_y;
}

void backward_move(t_game *game)
{
	double move_steps;
	double new_position_x;
	double new_position_y;

	game->player.move_direction = -1;
	new_position_x = game->player.position_x;
	new_position_y = game->player.position_y;
	move_steps = game->player.move_direction * game->player.move_speed;
	new_position_x += cos(game->player.angle_rotation) * move_steps;
	new_position_y += sin(game->player.angle_rotation) * move_steps;
	if (!check_map(game, new_position_x, new_position_y))
		return ;
	game->player.position_x = new_position_x;
	game->player.position_y = new_position_y;
}

void forward_move(t_game *game)
{
	double move_steps;
	double new_position_x;
	double new_position_y;

	game->player.move_direction = 1;
	new_position_x = game->player.position_x;
	new_position_y = game->player.position_y;
	move_steps = game->player.move_direction * game->player.move_speed;
	new_position_x += cos(game->player.angle_rotation) * move_steps;
	new_position_y += sin(game->player.angle_rotation) * move_steps;
	if (!check_map(game, new_position_x, new_position_y))
		return ;
	game->player.position_x = new_position_x;
	game->player.position_y = new_position_y;
}
