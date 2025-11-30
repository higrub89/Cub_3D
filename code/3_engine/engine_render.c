/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:01:55 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/25 13:29:28 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_put_pixel(t_grl *grl, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= grl->engine.win_w || y < 0 || y >= grl->engine.win_h)
		return ;
	dst = grl->engine.screen_buff.addr + (y * grl->engine.screen_buff.line_len
			+ x * (grl->engine.screen_buff.bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_render_floor_ceiling(t_grl *grl)
{
	t_img	*buff;
	int		*ptr;
	int		x;
	int		y;
	int		color;

	buff = &grl->engine.screen_buff;
	y = -1;
	while (++y < grl->engine.win_h)
	{
		ptr = (int *)(buff->addr + (y * buff->line_len));
		color = grl->assets.colors_rgb[y < grl->engine.win_h / 2];
		x = -1;
		while (++x < grl->engine.win_w)
		{
			*ptr = color;
			ptr++;
		}
	}
}

static int	ft_get_texture_color(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static void	ft_draw_texture_stripe(t_grl *grl, t_ray *ray, int x)
{
	int	y;
	int	tex_y;
	int	tex_id;
	int	color;

	if (ray->side == 0)
		tex_id = 2 + (ray->ray_dir_x > 0);
	else
		tex_id = 0 + (ray->ray_dir_y > 0);
	ray->step = 1.0 * 64 / ray->line_height;
	ray->tex_pos = (ray->draw_start - grl->engine.win_h / 2 + ray->line_height
			/ 2) * ray->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos & (64 - 1);
		ray->tex_pos += ray->step;
		color = ft_get_texture_color(&grl->engine.textures[tex_id], ray->tex_x,
				tex_y);
		ft_put_pixel(grl, x, y, color);
		y++;
	}
}

void	ft_raycast_walls(t_grl *grl)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < grl->engine.win_w)
	{
		ft_init_ray(&ray, grl, x);
		ft_calc_step(&ray, grl);
		ft_perform_dda(&ray, grl);
		ft_calc_wall_height(&ray, grl);
		ft_calc_texture_x(&ray, grl);
		ft_draw_texture_stripe(grl, &ray, x);
		x++;
	}
}
