/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:05:21 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 19:19:13 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "linear_algebra.h"
#include "duke.h"

t_vertex	lines_intersect_p(t_vertex a1, t_vertex a2, \
										t_vertex b1, t_vertex b2)
{
	t_vertex	l1;
	t_vertex	l2;
	t_vertex	ret;

	l1 = get_line_by_points(a1, a2);
	l2 = get_line_by_points(b1, b2);
	ret = lines_intersect(l1, l2);
	return (ret);
}

t_vertex	get_line_by_points(t_vertex f, t_vertex s)
{
	t_vertex	ret;

	ret.x = f.y - s.y;
	ret.y = s.x - f.x;
	ret.z = f.x * s.y - s.x * f.y;
	return (ret);
}

t_vertex	get_ort_line_by_point(t_vertex line, t_vertex p)
{
	t_vertex	ret;

	ret.x = -line.y;
	ret.y = line.x;
	ret.z = -line.x * p.y + line.y * p.x;
	return (ret);
}

t_vertex	lines_intersect(t_vertex l1, t_vertex l2)
{
	t_vertex	ret;

	if (l2.x * l1.y - l1.x * l2.y != 0)
	{
		ret.x = (l2.y * l1.z - l1.y * l2.z) / \
				(l2.x * l1.y - l1.x * l2.y);
		if (l1.y != 0)
			ret.y = (-l1.x * ret.x - l1.z) / l1.y;
		else
			ret.y = (-l2.x * ret.x - l2.z) / l2.y;
	}
	else
	{
		ret.x = (l1.y * l2.z - l2.y * l1.z) / \
				(l1.x * l2.y - l2.x * l1.y);
		if (l2.y != 0)
			ret.y = (-l2.x * ret.x - l2.z) / l2.y;
		else
			ret.y = (-l1.x * ret.x - l1.z) / l1.y;
	}
	ret.z = 0.0;
	return (ret);
}
