/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanUp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:24:13 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/25 14:13:16 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	ft_free_engine(t_grl *grl)
{
	int	i;

	if (grl->engine.screen_buff.img_ptr)
		mlx_destroy_image(grl->engine.mlx, grl->engine.screen_buff.img_ptr);
	i = 0;
	while (i < 4)
	{
		if (grl->engine.textures[i].img_ptr)
			mlx_destroy_image(grl->engine.mlx, grl->engine.textures[i].img_ptr);
		i++;
	}
	if (grl->engine.win)
		mlx_destroy_window(grl->engine.mlx, grl->engine.win);
	if (grl->engine.mlx)
	{
		mlx_destroy_display(grl->engine.mlx);
		free(grl->engine.mlx);
	}
}

void	ft_ctrl_cleanup(t_grl *grl, char *sterror, int exit_code)
{
	if (exit_code == 1)
		ft_print_error(sterror);
	ft_free(grl);
	exit(exit_code);
}

void	ft_print_error(char *sterror)
{
	ssize_t	ret;

	if (sterror)
	{
		ret = write(2, "Error\n", 6);
		ret = write(2, sterror, ft_strlen(sterror));
		ret = write(2, "\n", 1);
	}
	else
	{
		ret = write(2, "Error\n", 6);
		perror(NULL);
	}
	(void)ret;
}

void	ft_free(t_grl *grl)
{
	int	i;

	if (!grl)
		return ;
	ft_free_engine(grl);
	i = -1;
	while (++i < 4)
		if (grl->assets.textures_path[i])
			free(grl->assets.textures_path[i]);
	if (grl->map)
		free(grl->map);
	if (grl->map_block)
		ft_free_array(grl->map_block);
	if (grl->solid_map)
	{
		i = -1;
		while (++i < grl->map_height)
			free(grl->solid_map[i]);
		free(grl->solid_map);
	}
}

void	ft_free_array(char **array)
{
	char	**ptr;

	if (!array)
		return ;
	ptr = array;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(array);
}
