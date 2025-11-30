/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B1_headers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:49:25 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 14:13:16 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_headers(t_grl *grl)
{
	int	i;

	if (!grl || !grl->map)
		ft_ctrl_cleanup(grl, "Map array missing", 1);
	ft_bzero(&grl->assets, sizeof(t_assets));
	grl->map_start = ft_find_map_start_index(grl, grl->map);
	grl->map_end = ft_find_map_end_index(grl, grl->map, grl->map_start);
	i = 0;
	while (i < grl->map_start)
	{
		if (!ft_is_line_empty(grl->map[i]))
			ft_process_header_line(grl, grl->map[i]);
		i++;
	}
	if (grl->assets.headers_mask != HDR_ALL_MASK)
		ft_ctrl_cleanup(grl, "Incomplete header section", 1);
}

int	ft_find_map_start_index(t_grl *grl, char **lines)
{
	int	i;

	if (!lines)
		ft_ctrl_cleanup(grl, "Lines array missing", 1);
	i = 0;
	while (lines[i] && ft_is_line_empty(lines[i]))
		i++;
	while (lines[i])
	{
		if (ft_is_map_line(lines[i]))
			return (i);
		i++;
	}
	ft_ctrl_cleanup(grl, "Map block not found", 1);
	return (-1);
}

int	ft_is_line_empty(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_map_line(char *line)
{
	int	i;
	int	has_tile;

	if (!line)
		return (0);
	i = 0;
	has_tile = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr("01NSEW", line[i]))
			has_tile = 1;
		else if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	if (has_tile == 0)
		return (0);
	return (1);
}

int	ft_find_map_end_index(t_grl *grl, char **lines, int map_start)
{
	int	i;
	int	last_map;

	if (!lines || map_start < 0 || !lines[map_start])
		ft_ctrl_cleanup(grl, "Invalid map start index", 1);
	i = map_start;
	last_map = map_start;
	while (lines[i])
	{
		if (ft_is_map_line(lines[i]))
			last_map = i;
		else if (ft_is_line_empty(lines[i]))
		{
			ft_guard_against_map_gap(grl, lines, i + 1);
			return (last_map);
		}
		else
			ft_ctrl_cleanup(grl, "Invalid content inside map", 1);
		i++;
	}
	return (last_map);
}
