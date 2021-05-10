/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:43:18 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/08 19:28:19 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	write_to_file(t_map *map, int fd)
{
	int		i;
	char	*ptr;

	ptr = malloc(256);
	i = 0;
	while (i < map->uvs_count)
	{
		ft_putstr_fd("vt ", fd);
		ptr = ftoa(map->uvs[i].x, 8, ptr);
		ft_putstr_fd(ptr, fd);
		ft_putstr_fd(" ", fd);
		ptr = ftoa(map->uvs[i].y, 8, ptr);
		ft_putstr_fd(ptr, fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	write_to_file_nrmls(ptr, fd, map);
	write_to_file_vts(ptr, fd, map);
	free(ptr);
}

void	bsp_export_traversal(t_bsp *node, t_map *map, t_bsp *root)
{
	t_vertex	pts[100];
	int			pts_count;

	if (node->is_leaf)
	{
		node->floor = map->circuits[node->circuit].floor;
		node->ceil = map->circuits[node->circuit].ceil;
		node->ceil_tex = map->circuits[node->circuit].ceil_tex;
		node->floor_tex = map->circuits[node->circuit].floor_tex;
		node->wall_tex = map->circuits[node->circuit].wall_tex;
		back_transform(node, pts, &pts_count);
		triangulate(node, pts, &pts_count);
		to_obj_format(node, map);
		return ;
	}
	else
	{
		bsp_export_traversal(node->front, map, root);
		bsp_export_traversal(node->back, map, root);
	}
}

void	bsp_top_bottom_traversal(t_bsp *node, t_map *map, t_bsp *root)
{
	if (node->is_leaf)
	{
		add_tops_bottoms(node, map, root);
		return ;
	}
	else
	{
		bsp_top_bottom_traversal(node->front, map, root);
		bsp_top_bottom_traversal(node->back, map, root);
	}
}

void	bsp_write_traversal(t_bsp *node, t_map *map, t_bsp *root, int fd)
{
	if (node->is_leaf)
	{
		write_vt_trs_to_file(node, fd);
		return ;
	}
	else
	{
		bsp_write_traversal(node->front, map, root, fd);
		bsp_write_traversal(node->back, map, root, fd);
	}
}

void	export_map(t_map_editor *ed)
{
	int		fd;
	char	*str;

	str = malloc(100001);
	if (str == NULL)
		exit(-2);
	fd = open("geometry.obj", O_RDWR | O_TRUNC | O_CREAT, 0640);
	ed->map.uvs_count = 0;
	ed->map.vts_count = 0;
	ed->map.nrmls_count = 0;
	ed->map.uvs = malloc(sizeof(t_vertex) * 3000);
	ed->map.vts = malloc(sizeof(t_vertex) * 3000);
	ed->map.nrmls = malloc(sizeof(t_vertex) * 3000);
	if (ed->map.uvs == NULL || ed->map.vts == NULL
		|| ed->map.nrmls == NULL)
		exit(-2);
	bsp_export_traversal(&ed->root, &ed->map, &ed->root);
	bsp_top_bottom_traversal(&ed->root, &ed->map, &ed->root);
	bsp_write_traversal(&ed->root, &ed->map, &ed->root, fd);
	close(fd);
	export_map_errors(str, ed);
	ft_putendl_fd("", fd);
	ft_putendl_fd(str, fd);
	close(fd);
	free (str);
}
