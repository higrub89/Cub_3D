/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:49:35 by almejia-          #+#    #+#             */
/*   Updated: 2025/11/25 15:14:40 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Controlador PARSEO - Recolecta Responsabilidades.
void	ft_ctrl_parse(t_grl *grl, const char *map_file)
{
	ft_map_array(grl, map_file);
	ft_headers(grl);
	ft_normalize_assets(grl);
	ft_prepare_map_block(grl);
}
