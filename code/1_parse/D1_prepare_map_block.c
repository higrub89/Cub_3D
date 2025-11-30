/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   D1_prepare_map_block.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:49:32 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 14:13:16 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	ft_clean_map_line(t_grl *grl, char *line);
static void	ft_validate_map_character(t_grl *grl, char c);
static void	ft_store_map_block(t_grl *grl);

void	ft_prepare_map_block(t_grl *grl)
{
	int	row;
	int	height;

	if (!grl || !grl->map)
		ft_ctrl_cleanup(grl, "Map data missing", 1);
	row = grl->map_start;
	height = 0;
	while (row <= grl->map_end)
	{
		ft_clean_map_line(grl, grl->map[row]);
		row++;
		height++;
	}
	ft_store_map_block(grl);
	grl->map_height = height;
}

void	ft_clean_map_line(t_grl *grl, char *line)
{
	int	col;

	if (!line)
		ft_ctrl_cleanup(grl, "Empty map line", 1);
	col = 0;
	while (line[col] != '\0')
	{
		ft_validate_map_character(grl, line[col]);
		col++;
	}
	if (col > grl->map_width)
		grl->map_width = col;
}

void	ft_validate_map_character(t_grl *grl, char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ')
		ft_ctrl_cleanup(grl, "Invalid map character", 1);
}

void	ft_store_map_block(t_grl *grl)
{
	int		row;
	int		col;
	char	**block;

	if (!grl->map)
		ft_ctrl_cleanup(grl, "Map array missing", 1);
	row = grl->map_start;
	block = (char **)malloc(sizeof(char *) * ((grl->map_end - row) + 2));
	if (!block)
		ft_ctrl_cleanup(grl, "Malloc failed", 1);
	col = 0;
	while (row <= grl->map_end)
	{
		block[col] = ft_strdup(grl->map[row]);
		if (!block[col])
			ft_ctrl_cleanup(grl, "Malloc failed", 1);
		row++;
		col++;
	}
	block[col] = NULL;
	grl->map_block = block;
}
