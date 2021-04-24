/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:58:51 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 22:00:02 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

int	bsp_solid_traversal(t_bsp *node, t_vertex pos, int mode, float height)
{
	if (node->is_leaf)
	{
		if (mode == PHISICS_MODE_PLAYER)
		{
			if (pos.z - (height - 0.2 - 0.4) < node->floor || \
				pos.z + 0.2 > node->ceil)
				return (0);
		}
		else
		{
			if (pos.z < node->floor || pos.z > node->ceil)
				return (0);
		}
		return (check_leaf(node, pos));
	}
	else
	{
		if (classify_point(pos, node->line, node->normal) == BACK)
			return (bsp_solid_traversal(node->front, pos, mode, height));
		else
			return (bsp_solid_traversal(node->back, pos, mode, height));
	}
}

int	if_possible_to_move(t_vertex pos, t_bsp *node, int mode, float height)
{
	return (bsp_solid_traversal(node, pos, mode, height));
}

void	get_floor_seil_traversal(t_bsp *node, t_vertex pos, \
											float *floor, float *ceil)
{
	if (node->is_leaf)
	{
		*floor = node->floor;
		*ceil = node->ceil;
	}
	else
	{
		if (classify_point(pos, node->line, node->normal) == BACK)
		{
			get_floor_seil_traversal(node->front, pos, floor, ceil);
		}
		else
		{
			get_floor_seil_traversal(node->back, pos, floor, ceil);
		}
	}
}
