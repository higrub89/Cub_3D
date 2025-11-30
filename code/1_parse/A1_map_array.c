/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A1_map_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:49:17 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 14:13:16 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// ** para comentarios de estructura.
// ** Recolector Responsabilidades.
void	ft_map_array(t_grl *grl, const char *map_file)
{
	int		fd;
	char	*buffer;
	int		line_count;

	ft_validate_file_extension(grl, map_file);
	fd = ft_open_file(grl, map_file);
	buffer = ft_read_file_content(grl, fd);
	line_count = ft_count_lines(buffer);
	grl->map = ft_allocate_lines_array(grl, line_count);
	ft_split_buffer_lines(buffer, grl->map);
	ft_close_file(grl, fd);
}

void	ft_validate_file_extension(t_grl *grl, const char *map_file)
{
	int	len;

	if (!map_file)
		ft_ctrl_cleanup(grl, "File does not exist", 1);
	len = ft_strlen(map_file);
	if (len < 4)
		ft_ctrl_cleanup(grl, "Filename wrong", 1);
	if (ft_strncmp(map_file + len - 4, ".cub", 4) != 0)
		ft_ctrl_cleanup(grl, "Wrong Extension", 1);
}

int	ft_open_file(t_grl *grl, const char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		ft_ctrl_cleanup(grl, NULL, 1);
	return (fd);
}

char	*ft_read_file_content(t_grl *grl, int fd)
{
	ssize_t		bytes_read;
	static char	buffer[100000];

	bytes_read = read(fd, buffer, 100000);
	if (bytes_read < 0)
		ft_ctrl_cleanup(grl, NULL, 1);
	if (bytes_read == 0)
		ft_ctrl_cleanup(grl, "File is empty", 1);
	buffer[bytes_read] = '\0';
	return (buffer);
}

int	ft_count_lines(char *buffer)
{
	int	i;
	int	line_count;

	i = 0;
	line_count = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			line_count++;
		i++;
	}
	if (i > 0 && buffer[i - 1] != '\n')
		line_count++;
	return (line_count);
}
