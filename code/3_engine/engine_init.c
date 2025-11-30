/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 23:02:28 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/25 15:49:14 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* Utilidad estática para reducir la verbosidad de acceso a texturas */
static void	ft_load_single_texture(t_grl *grl, int id, char *path)
{
	t_img	*tex;

	if (!path)
		ft_ctrl_cleanup(grl, "Error: Texture path is NULL", 1);
	tex = &grl->engine.textures[id];
	tex->img_ptr = mlx_xpm_file_to_image(grl->engine.mlx, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		printf("Error loading texture ID %d: %s\n", id, path);
		ft_ctrl_cleanup(grl, "Error: mlx_xpm_file_to_image failed", 1);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
}

void	ft_load_textures(t_grl *grl)
{
	ft_load_single_texture(grl, HDR_NO, grl->assets.textures_path[HDR_NO]);
	ft_load_single_texture(grl, HDR_SO, grl->assets.textures_path[HDR_SO]);
	ft_load_single_texture(grl, HDR_WE, grl->assets.textures_path[HDR_WE]);
	ft_load_single_texture(grl, HDR_EA, grl->assets.textures_path[HDR_EA]);
	printf("✅ MOTOR: Textures loaded correctly.\n");
}

/* Usamos un puntero 'buff' para evitar líneas > 80 columnas */
void	ft_init_screen_buffer(t_grl *grl)
{
	t_img	*buff;

	buff = &grl->engine.screen_buff;
	buff->img_ptr = mlx_new_image(grl->engine.mlx,
			grl->engine.win_w, grl->engine.win_h);
	if (!buff->img_ptr)
		ft_ctrl_cleanup(grl, "Error: mlx_new_image() failed", 1);
	buff->addr = mlx_get_data_addr(buff->img_ptr, &buff->bpp,
			&buff->line_len, &buff->endian);
	buff->width = grl->engine.win_w;
	buff->height = grl->engine.win_h;
	printf("✅ RENDER: Screen buffer initialized (%dx%d).\n",
		grl->engine.win_w, grl->engine.win_h);
}

static void	ft_optimize_window_size(t_grl *grl)
{
	int	safe_w;
	int	safe_h;

	safe_w = 20;
	safe_h = 70;
	mlx_get_screen_size(grl->engine.mlx, &grl->engine.win_w,
		&grl->engine.win_h);
	grl->engine.win_w -= safe_w;
	grl->engine.win_h -= safe_h;
	if (grl->engine.win_w < 320)
		grl->engine.win_w = 320;
	if (grl->engine.win_h < 240)
		grl->engine.win_h = 240;
	printf("✅ ENGINE: Display Resolution Optimized: %dx%d\n",
		grl->engine.win_w, grl->engine.win_h);
}

void	ft_init_motor(t_grl *grl)
{
	grl->engine.mlx = mlx_init();
	if (!grl->engine.mlx)
		ft_ctrl_cleanup(grl, "Error: mlx_init() failed", 1);
	ft_optimize_window_size(grl);
	grl->engine.win = mlx_new_window(grl->engine.mlx, grl->engine.win_w,
			grl->engine.win_h, "Ruben's Cub3D - Hyperluxury Edition");
	if (!grl->engine.win)
		ft_ctrl_cleanup(grl, "Error: mlx_new_window() failed", 1);
	ft_init_screen_buffer(grl);
	ft_load_textures(grl);
}
