/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 23:04:53 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/25 10:34:06 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_init_ray(t_ray *ray, t_grl *grl, int x)
{
	ray->camera_x = 2 * x / (double)grl->engine.win_w - 1;
	ray->ray_dir_x = grl->player.dir_x + grl->player.plane_x * ray->camera_x;
	ray->ray_dir_y = grl->player.dir_y + grl->player.plane_y * ray->camera_x;
	ray->map_x = (int)grl->player.pos_x;
	ray->map_y = (int)grl->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	ft_calc_step(t_ray *ray, t_grl *grl)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (grl->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - grl->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (grl->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - grl->player.pos_y)
			* ray->delta_dist_y;
	}
}

void	ft_perform_dda(t_ray *ray, t_grl *grl)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= grl->map_width || ray->map_y < 0
			|| ray->map_y >= grl->map_height)
		{
			ray->hit = 1;
			break ;
		}
		if (grl->map_block[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	ft_calc_wall_height(t_ray *ray, t_grl *grl)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(grl->engine.win_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + grl->engine.win_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + grl->engine.win_h / 2;
	if (ray->draw_end >= grl->engine.win_h)
		ray->draw_end = grl->engine.win_h - 1;
}

void	ft_calc_texture_x(t_ray *ray, t_grl *grl)
{
	if (ray->side == 0)
		ray->wall_x = grl->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = grl->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (double)64);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = 64 - ray->tex_x - 1;
}
