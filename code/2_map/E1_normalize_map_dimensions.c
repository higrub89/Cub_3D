/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   E1_normalize_map_dimensions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:50:15 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 14:15:13 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	ft_find_max_width(t_grl *grl);
static void	ft_pad_map_lines(t_grl *grl, int max_width);
static char	*ft_pad_line(t_grl *grl, char *line, int current_len,
				int target_len);

// R5 - Normalizar dimensiones del mapa (rectangular uniforme)
void	ft_normalize_map_dimensions(t_grl *grl)
{
	int	max_width;

	if (!grl || !grl->map_block)
		ft_ctrl_cleanup(grl, "Map block missing", 1);
	max_width = ft_find_max_width(grl);
	ft_pad_map_lines(grl, max_width);
	grl->map_width = max_width;
}

int	ft_find_max_width(t_grl *grl)
{
	int	row;
	int	max_width;
	int	line_len;

	if (!grl->map_block || grl->map_height <= 0)
		ft_ctrl_cleanup(grl, "Invalid map dimensions", 1);
	max_width = 0;
	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			ft_ctrl_cleanup(grl, "Map line missing", 1);
		line_len = ft_strlen(grl->map_block[row]);
		if (line_len > max_width)
			max_width = line_len;
		row++;
	}
	return (max_width);
}

void	ft_pad_map_lines(t_grl *grl, int max_width)
{
	int		row;
	int		line_len;
	char	*padded;

	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			ft_ctrl_cleanup(grl, "Map line missing", 1);
		line_len = ft_strlen(grl->map_block[row]);
		if (line_len < max_width)
		{
			padded = ft_pad_line(grl, grl->map_block[row], line_len, max_width);
			if (!padded)
				ft_ctrl_cleanup(grl, "Malloc failed", 1);
			free(grl->map_block[row]);
			grl->map_block[row] = padded;
		}
		row++;
	}
}

char	*ft_pad_line(t_grl *grl, char *line, int current_len, int target_len)
{
	char	*padded;
	int		i;

	(void)grl;
	padded = (char *)malloc(sizeof(char) * (target_len + 1));
	if (!padded)
		return (NULL);
	i = 0;
	while (i < current_len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < target_len)
	{
		padded[i] = ' ';
		i++;
	}
	padded[target_len] = '\0';
	return (padded);
}
