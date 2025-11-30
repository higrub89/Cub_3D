/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 23:03:23 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/24 10:37:54 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include <sys/time.h>

double	get_delta_time(t_grl *grl)
{
	struct timeval	time;
	double			current_time;
	double			delta;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec + (time.tv_usec / 1000000.0);
	if (grl->old_time == 0)
		grl->old_time = current_time;
	delta = current_time - grl->old_time;
	grl->old_time = current_time;
	return (delta);
}

void	ft_rotate_player_pro(t_grl *grl, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = grl->player.dir_x;
	grl->player.dir_x = grl->player.dir_x * cos(rot_speed) - grl->player.dir_y
		* sin(rot_speed);
	grl->player.dir_y = old_dir_x * sin(rot_speed) + grl->player.dir_y
		* cos(rot_speed);
	old_plane_x = grl->player.plane_x;
	grl->player.plane_x = grl->player.plane_x * cos(rot_speed)
		- grl->player.plane_y * sin(rot_speed);
	grl->player.plane_y = old_plane_x * sin(rot_speed) + grl->player.plane_y
		* cos(rot_speed);
}

static void	ft_apply_move(t_grl *grl, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	margin_x;
	double	margin_y;

	margin_x = 0.1;
	margin_y = 0.1;
	if (move_x < 0)
		margin_x = -0.1;
	if (move_y < 0)
		margin_y = -0.1;
	new_x = grl->player.pos_x + move_x;
	new_y = grl->player.pos_y + move_y;
	if (grl->map_block[(int)grl->player.pos_y][(int)(new_x + margin_x)] != '1')
		grl->player.pos_x = new_x;
	if (grl->map_block[(int)(new_y + margin_y)][(int)grl->player.pos_x] != '1')
		grl->player.pos_y = new_y;
}

void	ft_move_player_pro(t_grl *grl, double speed)
{
	double	mx;
	double	my;
	int		move;
	int		strafe;

	move = grl->keys.w - grl->keys.s;
	strafe = grl->keys.d - grl->keys.a;
	if (move == 0 && strafe == 0)
		return ;
	mx = (move * grl->player.dir_x) + (strafe * grl->player.plane_x);
	my = (move * grl->player.dir_y) + (strafe * grl->player.plane_y);
	ft_apply_move(grl, mx * speed, my * speed);
}
