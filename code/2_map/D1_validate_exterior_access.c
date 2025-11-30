/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   D1_validate_exterior_access.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:50:11 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 14:13:16 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	**ft_create_visited_array(t_grl *grl);
static int	*ft_allocate_visited_row(int line_len);
static void	ft_init_visited_row(int *row, int line_len);

// R4 - Detectar espacios vacíos accesibles desde el exterior
void	ft_validate_exterior_access(t_grl *grl)
{
	int	**visited;
	int	row;

	if (!grl || !grl->map_block)
		ft_ctrl_cleanup(grl, "Map block missing", 1);
	visited = ft_create_visited_array(grl);
	if (!visited)
		ft_ctrl_cleanup(grl, "Malloc failed", 1);
	ft_flood_fill_from_borders(grl, visited);
	ft_check_accessible_spaces(grl, visited);
	row = 0;
	while (row < grl->map_height)
	{
		free(visited[row]);
		row++;
	}
	free(visited);
}

int	**ft_create_visited_array(t_grl *grl)
{
	int	**visited;
	int	row;
	int	line_len;

	visited = (int **)malloc(sizeof(int *) * grl->map_height);
	if (!visited)
		return (NULL);
	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			return (NULL);
		line_len = ft_strlen(grl->map_block[row]);
		visited[row] = ft_allocate_visited_row(line_len);
		if (!visited[row])
			return (NULL);
		ft_init_visited_row(visited[row], line_len);
		row++;
	}
	return (visited);
}

int	*ft_allocate_visited_row(int line_len)
{
	return ((int *)malloc(sizeof(int) * line_len));
}

void	ft_init_visited_row(int *row, int line_len)
{
	int	col;

	col = 0;
	while (col < line_len)
	{
		row[col] = 0;
		col++;
	}
}
