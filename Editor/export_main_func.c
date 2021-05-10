/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:46:44 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/08 20:21:36 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_bsp	*get_node_by_wall_traversal(t_bsp *node, t_wall wall)
{
	int		i;

	if (node->is_leaf)
	{
		i = 0;
		while (i < node->walls_count)
		{
			if (length(sub(wall.points[0], node->walls[i].points[1])) < 0.1
				&& length(sub(wall.points[1], node->walls[i].points[0])) < 0.1)
			{
				return (node);
			}
			i++;
		}
	}
	else
	{
		return (get_node_by_wall_traversal(node->front, wall));
		return (get_node_by_wall_traversal(node->back, wall));
	}
	return (NULL);
}

t_tr	create_tr(t_vertex *pts, int *pts_count, int i)
{
	t_tr	res;

	res.points[0] = pts[i];
	res.points[1] = pts[get_i_plus_1(i, *pts_count)];
	res.points[2] = pts[get_i_plus_2(i, *pts_count)];
	delete_by_index(pts, get_i_plus_1(i, *pts_count), pts_count);
	return (res);
}

void	check_figure(int i, t_bsp *node, t_vertex *pts, int *pts_count)
{
	if (check_in_figure(pts, *pts_count, i) == 1)
	{
		node->trs[node->trs_count] = create_tr(pts, pts_count, i);
		(node->trs_count)++;
	}
	else
		i = get_i_plus_1(i, *pts_count);
}

void	triangulate(t_bsp *node, t_vertex *pts, int *pts_count)
{
	int			i;
	int			p;
	int			counter;

	i = 0;
	p = 0;
	counter = 0;
	node->trs = malloc(sizeof(t_tr) * 2000);
	if (node->trs == NULL)
		exit(-2);
	node->trs_count = 0;
	while (*pts_count > 3)
	{
		check_figure(i, node, pts, pts_count);
		counter++;
		if (counter > 1000000)
		{
			ft_putendl("Ошибка триангуляции");
			exit(-2);
		}
	}
	node->trs[node->trs_count] = create_tr(pts, pts_count, 0);
	(node->trs_count)++;
}
