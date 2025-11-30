/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   H1_calculate_final_dimensions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:50:24 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 14:13:16 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	ft_verify_map_height(t_grl *grl);
static void	ft_verify_map_width(t_grl *grl);
static void	ft_validate_minimum_size(t_grl *grl);
static void	ft_validate_reasonable_size(t_grl *grl);

// R8 - Calcular y almacenar dimensiones finales del mapa normalizado
void	ft_calculate_final_dimensions(t_grl *grl)
{
	if (!grl || !grl->map_block)
		ft_ctrl_cleanup(grl, "Map block missing", 1);
	ft_verify_map_height(grl);
	ft_verify_map_width(grl);
	ft_validate_minimum_size(grl);
}

void	ft_verify_map_height(t_grl *grl)
{
	int	count;
	int	row;

	if (!grl->map_block)
		ft_ctrl_cleanup(grl, "Map block missing", 1);
	count = 0;
	row = 0;
	while (grl->map_block[row])
	{
		count++;
		row++;
	}
	if (count != grl->map_height)
		ft_ctrl_cleanup(grl, "Map height mismatch", 1);
}

void	ft_verify_map_width(t_grl *grl)
{
	int	row;
	int	line_len;

	if (!grl->map_block || grl->map_height <= 0)
		ft_ctrl_cleanup(grl, "Invalid map dimensions", 1);
	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			ft_ctrl_cleanup(grl, "Map line missing", 1);
		line_len = ft_strlen(grl->map_block[row]);
		if (line_len != grl->map_width)
			ft_ctrl_cleanup(grl, "Map width mismatch", 1);
		row++;
	}
}

void	ft_validate_minimum_size(t_grl *grl)
{
	if (!grl)
		ft_ctrl_cleanup(grl, "Invalid map structure", 1);
	if (grl->map_height <= 0)
		ft_ctrl_cleanup(grl, "Map height too small", 1);
	if (grl->map_width <= 0)
		ft_ctrl_cleanup(grl, "Map width too small", 1);
	ft_validate_reasonable_size(grl);
}

void	ft_validate_reasonable_size(t_grl *grl)
{
	if (grl->map_height > 1000)
		ft_ctrl_cleanup(grl, "Map height too large", 1);
	if (grl->map_width > 1000)
		ft_ctrl_cleanup(grl, "Map width too large", 1);
}
