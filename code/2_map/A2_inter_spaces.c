/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A2_inter_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:49:41 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 16:07:02 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	ft_check_internal_cell(t_grl *grl, int row, int col);
static int	ft_is_internal_cell(t_grl *grl, int row, int col);
static int	ft_is_space_surrounded(t_grl *grl, int row, int col);
static int	ft_check_adjacent_cells(t_grl *grl, int row, int col);

void	ft_validate_internal_spaces(t_grl *grl)
{
	int	row;
	int	col;
	int	line_len;

	if (!grl->map_block)
		ft_ctrl_cleanup(grl, "Map block missing", 1);
	row = 1;
	while (row < grl->map_height - 1)
	{
		if (!grl->map_block[row])
			ft_ctrl_cleanup(grl, "Map line missing", 1);
		line_len = ft_strlen(grl->map_block[row]);
		col = 1;
		while (col < line_len - 1)
		{
			ft_check_internal_cell(grl, row, col);
			col++;
		}
		row++;
	}
}

static void	ft_check_internal_cell(t_grl *grl, int row, int col)
{
	if (ft_is_internal_cell(grl, row, col))
	{
		if (!ft_is_space_surrounded(grl, row, col))
			ft_ctrl_cleanup(grl, "Internal space not closed", 1);
	}
}

static int	ft_is_internal_cell(t_grl *grl, int row, int col)
{
	if (grl->map_block[row][col] == '0')
		return (1);
	if (ft_strchr("NSEW", grl->map_block[row][col]))
		return (1);
	return (0);
}

static int	ft_is_space_surrounded(t_grl *grl, int row, int col)
{
	int	line_len;

	if (row <= 0 || row >= grl->map_height - 1)
		return (0);
	if (!grl->map_block[row] || !grl->map_block[row - 1]
		|| !grl->map_block[row + 1])
		return (0);
	line_len = ft_strlen(grl->map_block[row]);
	if (col <= 0 || col >= line_len - 1)
		return (0);
	if (!ft_check_adjacent_cells(grl, row, col))
		return (0);
	return (1);
}

static int	ft_check_adjacent_cells(t_grl *grl, int row, int col)
{
	int		prev_len;
	int		next_len;
	char	adj;

	prev_len = ft_strlen(grl->map_block[row - 1]);
	next_len = ft_strlen(grl->map_block[row + 1]);
	if (col < prev_len)
	{
		adj = grl->map_block[row - 1][col];
		if (adj == ' ')
			return (0);
	}
	if (col < next_len)
	{
		adj = grl->map_block[row + 1][col];
		if (adj == ' ')
			return (0);
	}
	if (grl->map_block[row][col - 1] == ' '
		|| grl->map_block[row][col + 1] == ' ')
		return (0);
	return (1);
}
