/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:25:10 by asalmi            #+#    #+#             */
/*   Updated: 2025/01/02 16:25:34 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool is_facing_down(double angle)
{
	return (angle > 0 && angle < M_PI);
}

bool is_facing_up(double angle)
{
	return (angle > M_PI && angle < 2 * M_PI);
}

bool is_facing_right(double angle)
{
	return (angle > 3 * M_PI / 2 || angle < M_PI / 2);
}

bool is_facing_left(double angle)
{
	return (angle > M_PI / 2 && angle < 3 * M_PI / 2);
}
