/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C1_normalize_assets.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:49:30 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 16:37:03 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	ft_normalize_texture(t_grl *grl, int idx);
static void	ft_normalize_color(t_grl *grl, int idx);
static char	*ft_trim_asset_value(char *value);
static int	ft_extract_component(t_grl *grl, char **cursor);

void	ft_normalize_assets(t_grl *grl)
{
	int	idx;

	if (!grl)
		ft_ctrl_cleanup(grl, "Normalize assets failed", 1);
	idx = 0;
	while (idx < 4)
	{
		ft_normalize_texture(grl, idx);
		idx++;
	}
	idx = 0;
	while (idx < 2)
	{
		ft_normalize_color(grl, idx);
		idx++;
	}
}

void	ft_normalize_texture(t_grl *grl, int idx)
{
	char	*raw;
	char	*clean;
	int		fd;

	raw = ft_trim_asset_value(grl->assets.textures_path[idx]);
	if (!raw || *raw == '\0')
		ft_ctrl_cleanup(grl, "Missing texture path", 1);
	clean = ft_strdup(raw);
	if (!clean)
		ft_ctrl_cleanup(grl, "Malloc failed", 1);
	fd = open(clean, O_RDONLY);
	if (fd < 0)
	{
		free(clean);
		ft_ctrl_cleanup(grl, "Texture path invalid", 1);
	}
	close(fd);
	if (grl->assets.textures_path[idx])
		free(grl->assets.textures_path[idx]);
	grl->assets.textures_path[idx] = clean;
}

char	*ft_trim_asset_value(char *value)
{
	int	len;

	if (!value)
		return (NULL);
	while (*value == ' ' || *value == '\t')
		value++;
	len = ft_strlen(value);
	while (len > 0 && (value[len - 1] == ' ' || value[len - 1] == '\t'))
	{
		value[len - 1] = '\0';
		len--;
	}
	return (value);
}

void	ft_normalize_color(t_grl *grl, int idx)
{
	char	*raw;
	char	*cursor;
	int		colors[3];
	int		i;

	raw = ft_trim_asset_value(grl->assets.colors[idx]);
	if (!raw || *raw == '\0')
		ft_ctrl_cleanup(grl, "Color value missing", 1);
	cursor = raw;
	i = 0;
	while (i < 3)
	{
		colors[i] = ft_extract_component(grl, &cursor);
		if (i < 2)
		{
			if (*cursor != ',')
				ft_ctrl_cleanup(grl, "Color format invalid", 1);
			cursor++;
		}
		i++;
	}
	if (*cursor != '\0')
		ft_ctrl_cleanup(grl, "Color format invalid", 1);
	grl->assets.colors_rgb[idx] = (colors[0] << 16)
		| (colors[1] << 8) | colors[2];
}

int	ft_extract_component(t_grl *grl, char **cursor)
{
	int	value;

	value = 0;
	while (**cursor == ' ' || **cursor == '\t')
		(*cursor)++;
	if (**cursor < '0' || **cursor > '9')
		ft_ctrl_cleanup(grl, "Color format invalid", 1);
	while (**cursor >= '0' && **cursor <= '9')
	{
		value = value * 10 + (**cursor - '0');
		if (value > 255)
			ft_ctrl_cleanup(grl, "Color range invalid", 1);
		(*cursor)++;
	}
	while (**cursor == ' ' || **cursor == '\t')
		(*cursor)++;
	return (value);
}
