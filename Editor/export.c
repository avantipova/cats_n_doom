/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:53:37 by ldeirdre          #+#    #+#             */
/*   Updated: 2021/05/06 18:43:56 by sreicher         ###   ########.fr       */
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

void	triangulate(t_bsp *node, t_vertex *pts, int *pts_count)
{
	int			i;
	int			p;
	int			counter;
	t_vertex	new1;
	t_vertex	new2;

	i = 0;
	p = 0;
	counter = 0;
	node->trs = malloc(sizeof(t_tr) * 2000);
	if (node->trs == NULL)
		exit(-2);
	node->trs_count = 0;
	while (*pts_count > 3)
	{
		new1 = (t_vertex){
			pts[i].x,
			pts[i].y,
			0.0};
		new2 = (t_vertex){
			pts[get_i_plus_2(i, *pts_count)].x,
			pts[get_i_plus_2(i, *pts_count)].y,
			0.0};
		if (check_in_figure(pts, *pts_count, i) == 1)
		{
			node->trs[node->trs_count] = create_tr(pts, pts_count, i);
			(node->trs_count)++;
		}
		else
		{
			i = get_i_plus_1(i, *pts_count);
		}
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

void	write_vt_trs_to_file(t_bsp *node, int fd)
{
	int		i;

	i = 0;
	if (!node->is_leaf)
		return ;
	while (i < node->vt_trs_count)
	{
		ft_putstr_fd("f ", fd);
		ft_putnbr_fd(node->vt_trs[i].ids[0] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].uv_ids[0] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].n_ids[0] + 1, fd);
		ft_putstr_fd(" ", fd);
		ft_putnbr_fd(node->vt_trs[i].ids[1] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].uv_ids[1] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].n_ids[1] + 1, fd);
		ft_putstr_fd(" ", fd);
		ft_putnbr_fd(node->vt_trs[i].ids[2] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].uv_ids[2] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].n_ids[2] + 1, fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	ft_putendl_fd("", fd);
}


