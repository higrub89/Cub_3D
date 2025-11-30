/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   D2_Flood.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:50:13 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 14:13:16 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	ft_is_border_position(t_grl *grl, int row, int col, int line_len);
static void	ft_process_border_cell(t_grl *grl, int **visited, int row, int col);
static void	ft_flood_fill(t_grl *grl, int **visited, int row, int col);

void	ft_flood_fill_from_borders(t_grl *grl, int **visited)
{
	int	row;
	int	col;
	int	line_len;

	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			return ;
		line_len = ft_strlen(grl->map_block[row]);
		col = 0;
		while (col < line_len)
		{
			if (ft_is_border_position(grl, row, col, line_len))
				ft_process_border_cell(grl, visited, row, col);
			col++;
		}
		row++;
	}
}

int	ft_is_border_position(t_grl *grl, int row, int col, int line_len)
{
	if (row == 0 || row == grl->map_height - 1)
		return (1);
	if (col == 0 || col == line_len - 1)
		return (1);
	return (0);
}

void	ft_process_border_cell(t_grl *grl, int **visited, int row, int col)
{
	if (grl->map_block[row][col] == ' '
		|| grl->map_block[row][col] == '0')
		ft_flood_fill(grl, visited, row, col);
}

void	ft_flood_fill(t_grl *grl, int **visited, int row, int col)
{
	int	line_len;

	if (row < 0 || row >= grl->map_height)
		return ;
	if (!grl->map_block[row])
		return ;
	line_len = ft_strlen(grl->map_block[row]);
	if (col < 0 || col >= line_len)
		return ;
	if (visited[row][col])
		return ;
	if (grl->map_block[row][col] == '1')
		return ;
	visited[row][col] = 1;
	ft_flood_fill(grl, visited, row - 1, col);
	ft_flood_fill(grl, visited, row + 1, col);
	ft_flood_fill(grl, visited, row, col - 1);
	ft_flood_fill(grl, visited, row, col + 1);
}

void	ft_check_accessible_spaces(t_grl *grl, int **visited)
{
	int	row;
	int	col;
	int	line_len;

	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			return ;
		line_len = ft_strlen(grl->map_block[row]);
		col = 0;
		while (col < line_len)
		{
			if (grl->map_block[row][col] == '0')
			{
				if (visited[row][col])
					ft_ctrl_cleanup(grl, "Space accessible from exterior", 1);
			}
			col++;
		}
		row++;
	}
}
