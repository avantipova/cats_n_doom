/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:34:25 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 17:34:44 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	sort_check_cont(t_triangle *triangle, \
					t_point *projected, int swap, t_point v_swap)
{
	if (projected[triangle->indexes[2]].y < projected[triangle->indexes[1]].y)
	{
		swap = triangle->indexes[1];
		triangle->indexes[1] = triangle->indexes[2];
		triangle->indexes[2] = swap;
		v_swap = triangle->uvs[1];
		triangle->uvs[1] = triangle->uvs[2];
		triangle->uvs[2] = v_swap;
	}
}

void	sort_vertex_indexes(t_triangle *triangle, t_point *projected)
{
	int		swap;
	t_point	v_swap;

	if (projected[triangle->indexes[1]].y < projected[triangle->indexes[0]].y)
	{
		swap = triangle->indexes[0];
		triangle->indexes[0] = triangle->indexes[1];
		triangle->indexes[1] = swap;
		v_swap = triangle->uvs[0];
		triangle->uvs[0] = triangle->uvs[1];
		triangle->uvs[1] = v_swap;
	}
	if (projected[triangle->indexes[2]].y < projected[triangle->indexes[0]].y)
	{
		swap = triangle->indexes[0];
		triangle->indexes[0] = triangle->indexes[2];
		triangle->indexes[2] = swap;
		v_swap = triangle->uvs[0];
		triangle->uvs[0] = triangle->uvs[2];
		triangle->uvs[2] = v_swap;
	}
	sort_check_cont(triangle, projected, swap, v_swap);
}
