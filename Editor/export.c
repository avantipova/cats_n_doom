/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:53:37 by ldeirdre          #+#    #+#             */
/*   Updated: 2021/05/08 19:44:44 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	back_transform(t_bsp *node, t_vertex *pts, int *pts_count)
{
	int		i;

	i = 0;
	*pts_count = 0;
	while (i < node->walls_count)
	{
		pts[i] = node->walls[i].points[1];
		(*pts_count)++;
		i++;
	}
}

int	check_in_figure(t_vertex *pts, int pts_count, int i)
{
	t_vertex	new;
	t_vertex	base;
	t_vertex	end;
	float		angle1;
	float		angle2;

	base = normalize((t_vertex){
			pts[get_i_minus_1(i, pts_count)].x - pts[i].x,
			pts[get_i_minus_1(i, pts_count)].y - pts[i].y,
			0.0});
	new = normalize((t_vertex){
			pts[get_i_plus_2(i, pts_count)].x - pts[i].x,
			pts[get_i_plus_2(i, pts_count)].y - pts[i].y,
			0.0});
	end = normalize((t_vertex){
			pts[get_i_plus_1(i, pts_count)].x - pts[i].x,
			pts[get_i_plus_1(i, pts_count)].y - pts[i].y,
			0.0});
	angle1 = new_less_zero(base, new);
	angle2 = end_less_zero(base, end);
	if (cross(base, end).z < 0.0)
		angle2 = 2 * M_PI - angle2;
	if (angle2 < angle1 && angle1 > 0.0)
		return (1);
	return (0);
}

int	add_n(t_map *map, t_vertex n)
{
	int		i;

	i = 0;
	while (i < map->nrmls_count)
	{
		if (map->nrmls[i].x == n.x && map->nrmls[i].y == n.y
			&& map->nrmls[i].z == n.z)
			return (i);
		i++;
	}
	map->nrmls[map->nrmls_count] = n;
	(map->nrmls_count)++;
	return (map->nrmls_count - 1);
}

int	add_vt(t_map *map, t_vertex vt)
{
	int		i;

	i = 0;
	while (i < map->vts_count)
	{
		if (map->vts[i].x == vt.x && map->vts[i].y == vt.y
			&& map->vts[i].z == vt.z)
			return (i);
		i++;
	}
	map->vts[map->vts_count] = vt;
	(map->vts_count)++;
	return (map->vts_count - 1);
}

int	add_uv(t_map *map, t_vertex uv)
{
	int		i;

	i = 0;
	while (i < map->uvs_count)
	{
		if (map->uvs[i].x == uv.x && map->uvs[i].y == uv.y)
			return (i);
		i++;
	}
	map->uvs[map->uvs_count] = uv;
	(map->uvs_count)++;
	return (map->uvs_count - 1);
}
