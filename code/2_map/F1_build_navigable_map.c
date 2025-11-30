/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   F1_build_navigable_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:50:18 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 14:15:24 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	**ft_allocate_solid_map(t_grl *grl);
static void	ft_fill_solid_map(t_grl *grl, int **solid_map);
static int	ft_is_solid_cell(char c);

// R6 - Construir estructura de datos navegable con información de solidez
void	ft_build_navigable_map(t_grl *grl)
{
	int	**solid_map;

	if (!grl || !grl->map_block)
		ft_ctrl_cleanup(grl, "Map block missing", 1);
	solid_map = ft_allocate_solid_map(grl);
	if (!solid_map)
		ft_ctrl_cleanup(grl, "Malloc failed", 1);
	ft_fill_solid_map(grl, solid_map);
	grl->solid_map = solid_map;
}

int	**ft_allocate_solid_map(t_grl *grl)
{
	int	**solid_map;
	int	row;

	solid_map = (int **)malloc(sizeof(int *) * grl->map_height);
	if (!solid_map)
		return (NULL);
	row = 0;
	while (row < grl->map_height)
	{
		solid_map[row] = (int *)malloc(sizeof(int) * grl->map_width);
		if (!solid_map[row])
			return (NULL);
		row++;
	}
	return (solid_map);
}

void	ft_fill_solid_map(t_grl *grl, int **solid_map)
{
	int	row;
	int	col;

	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			ft_ctrl_cleanup(grl, "Map line missing", 1);
		col = 0;
		while (col < grl->map_width)
		{
			solid_map[row][col] = ft_is_solid_cell(grl->map_block[row][col]);
			col++;
		}
		row++;
	}
}

int	ft_is_solid_cell(char c)
{
	if (c == '1')
		return (1);
	return (0);
}
