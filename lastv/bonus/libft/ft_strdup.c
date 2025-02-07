/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:59:14 by mizem             #+#    #+#             */
/*   Updated: 2025/01/20 22:05:07 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

char	*ft_strdup(char *s1)
{
	int	i;
	int	y;
	char	*dst;

	i = ft_strlen(s1);
	y = 0;
	dst = malloc((i + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (s1[y])
	{
		dst[y] = s1[y];
		y++;
	}
	dst[y] = '\0';
	return (dst);
}
