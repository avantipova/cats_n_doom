/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:11:06 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/08 19:26:56 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

float	new_less_zero(t_vertex base, t_vertex new)
{
	double	angle1;

	angle1 = acosf(dot(base, new));
	if (cross(base, new).z < 0.0)
		angle1 = 2 * M_PI - angle1;
	return (angle1);
}

float	end_less_zero(t_vertex base, t_vertex end)
{
	double	angle2;

	angle2 = acosf(dot(base, end));
	if (cross(base, end).z < 0.0)
		angle2 = 2 * M_PI - angle2;
	return (angle2);
}

void	write_to_file_vts(char *ptr, int fd, t_map *map)
{
	int		i;

	i = 0;
	while (i < map->vts_count)
	{
		ft_putstr_fd("v ", fd);
		ptr = ftoa(map->vts[i].x, 8, ptr);
		ft_putstr_fd(ptr, fd);
		ft_putstr_fd(" ", fd);
		ptr = ftoa(map->vts[i].z, 8, ptr);
		ft_putstr_fd(ptr, fd);
		ft_putstr_fd(" ", fd);
		ptr = ftoa(map->vts[i].y, 8, ptr);
		ft_putstr_fd(ptr, fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

void	write_to_file_nrmls(char *ptr, int fd, t_map *map)
{
	int		i;

	i = 0;
	while (i < map->nrmls_count)
	{
		ft_putstr_fd("vn ", fd);
		ptr = ftoa(map->nrmls[i].x, 8, ptr);
		ft_putstr_fd(ptr, fd);
		ft_putstr_fd(" ", fd);
		ptr = ftoa(map->nrmls[i].z, 8, ptr);
		ft_putstr_fd(ptr, fd);
		ft_putstr_fd(" ", fd);
		ptr = ftoa(map->nrmls[i].y, 8, ptr);
		ft_putstr_fd(ptr, fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

void	export_map_errors(char *str, t_map_editor *ed)
{
	int		fd;

	fd = open("geometry.obj", O_RDWR);
	if (fd < 0)
	{
		ft_putendl("Ошибка сохранения");
		exit(-2);
	}
	str[read(fd, str, 100000)] = 0;
	close(fd);
	ft_putendl(str);
	fd = open("geometry.obj", O_RDWR | O_TRUNC);
	if (fd < 0)
	{
		ft_putendl("Ошибка сохранения");
		exit(-2);
	}
	write_to_file(&ed->map, fd);
	close(fd);
	fd = open("geometry.obj", O_RDWR | O_APPEND);
	if (fd < 0)
	{
		ft_putendl("Ошибка сохранения");
		exit(-2);
	}
}
