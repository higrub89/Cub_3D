/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A2_map_array_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:49:22 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 14:13:16 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	**ft_allocate_lines_array(t_grl *grl, int line_count)
{
	char	**lines;

	lines = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		ft_ctrl_cleanup(grl, "Malloc failed", 1);
	return (lines);
}

void	ft_split_buffer_lines(char *buffer, char **map)
{
	int	i;
	int	start;
	int	map_idx;

	i = 0;
	start = 0;
	map_idx = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			map[map_idx] = &buffer[start];
			start = i + 1;
			map_idx++;
		}
		i++;
	}
	if (start < i)
		map[map_idx++] = &buffer[start];
	map[map_idx] = NULL;
}

void	ft_close_file(t_grl *grl, int fd)
{
	if (close(fd) < 0)
		ft_ctrl_cleanup(grl, NULL, 1);
}
