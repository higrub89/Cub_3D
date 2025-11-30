/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   G1_store_player_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:50:21 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 14:15:39 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	ft_search_player_in_row(t_grl *grl, int row);
static int	ft_get_player_direction(char c);
static int	ft_is_player_char(char c);

// R7 - Almacenar posición inicial del jugador (coordenadas y dirección)
void	ft_store_player_start(t_grl *grl)
{
	int	row;

	if (!grl || !grl->map_block)
		ft_ctrl_cleanup(grl, "Map block missing", 1);
	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			ft_ctrl_cleanup(grl, "Map line missing", 1);
		if (ft_search_player_in_row(grl, row))
			return ;
		row++;
	}
}

int	ft_search_player_in_row(t_grl *grl, int row)
{
	int	col;

	col = 0;
	while (col < grl->map_width)
	{
		if (ft_is_player_char(grl->map_block[row][col]))
		{
			grl->player_row = row;
			grl->player_col = col;
			grl->player_dir = ft_get_player_direction(grl->map_block[row][col]);
			return (1);
		}
		col++;
	}
	return (0);
}

int	ft_get_player_direction(char c)
{
	if (c == 'N')
		return (0);
	if (c == 'S')
		return (1);
	if (c == 'E')
		return (2);
	if (c == 'W')
		return (3);
	return (-1);
}

int	ft_is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
