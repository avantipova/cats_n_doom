/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:00:18 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 21:59:06 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

int	classify_point_s(t_vertex cam, t_vertex line, t_vertex normal)
{
	t_vertex	new;
	t_vertex	ort;

	cam.z = 0.0;
	normal.z = 0.0;
	ort = get_ort_line_by_point(line, cam);
	new = lines_intersect(line, ort);
	new.z = 0.0;
	new = sub(cam, new);
	if (dot(new, normal) < 0.0)
		return (BACK);
	return (FRONT);
}

int	check_leaf(t_bsp *node, t_vertex pos)
{
	int			i;
	t_vertex	line;

	i = 0;
	while (i < node->walls_count)
	{
		node->walls[i].failed = 0;
		if (node->walls[i].type == WALL_TYPE_WALL)
		{
			node->walls[i].failed = 1;
			line = get_line_by_points(node->walls[i].points[0], \
							node->walls[i].points[1]);
			if (classify_point_s(pos, line, node->walls[i].normal) == BACK)
			{
				node->walls[i].failed = 2;
				return (0);
			}
		}
		i++;
	}
	return (1);
}
