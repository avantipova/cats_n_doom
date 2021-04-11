/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_property.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:36:12 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 20:05:30 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

char	*read_property_3(t_bsp *node, char *key, char *ptr)
{
	if (!ft_strcmp(key, "walls"))
	{
		ptr = ft_strchr(ptr, '[') + 1;
		ptr = read_walls(node, ptr);
		return (ptr);
	}
	else if (!ft_strcmp(key, "vt_trs"))
	{
		ptr = ft_strchr(ptr, '[') + 1;
		ptr = read_vt_trs(node, ptr);
		return (ptr);
	}
	else if (!ft_strcmp(key, "front"))
	{
		ptr = ft_strchr(ptr, '{') + 1;
		node->front = (t_bsp *)malloc(sizeof(t_bsp));
		return (read_node(node->front, ptr));
	}
	else if (!ft_strcmp(key, "back"))
	{
		ptr = ft_strchr(ptr, '{') + 1;
		node->back = (t_bsp *)malloc(sizeof(t_bsp));
		return (read_node(node->back, ptr));
	}
	return (NULL);
}

char	*read_property_2(t_bsp *node, char *key, char *ptr)
{
	if (!ft_strcmp(key, "floor_tex"))
	{
		node->floor_tex = ft_atoi(ptr);
		while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
			ptr++;
		return (ft_strchr(ptr, ','));
	}
	else if (!ft_strcmp(key, "line"))
	{
		ptr = ft_strchr(ptr, '[') + 1;
		node->line.x = ft_atof(ptr);
		ptr = ft_strchr(ptr, ',') + 1;
		node->line.y = ft_atof(ptr);
		return (ft_strchr(ptr, ']') + 1);
	}
	else if (!ft_strcmp(key, "normal"))
	{
		ptr = ft_strchr(ptr, '[') + 1;
		node->normal.x = ft_atof(ptr);
		ptr = ft_strchr(ptr, ',') + 1;
		node->normal.y = ft_atof(ptr);
		return (ft_strchr(ptr, ']') + 1);
	}
	else
		return (read_property_3(node, key, ptr));
}

char	*read_property_1(t_bsp *node, char *key, char *ptr)
{
	if (!ft_strcmp(key, "ceil"))
	{
		node->ceil = ft_atof(ptr);
		while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
			ptr++;
		return (ft_strchr(ptr, ','));
	}
	else if (!ft_strcmp(key, "wall_tex"))
	{
		node->wall_tex = ft_atoi(ptr);
		while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
			ptr++;
		return (ft_strchr(ptr, ','));
	}
	else if (!ft_strcmp(key, "ceil_tex"))
	{
		node->ceil_tex = ft_atoi(ptr);
		while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
			ptr++;
		return (ft_strchr(ptr, ','));
	}
	else
		return (read_property_2(node, key, ptr));
}

char	*read_property(t_bsp *node, char *str)
{
	char	key[32];
	char	*ptr;

	ft_strncpy(key, str, ft_strchr(str, '"') - str);
	key[ft_strchr(str, '"') - str] = 0;
	puts(key);
	ptr = ft_strchr(str, ':') + 1;
	if (!ft_strcmp(key, "isLeaf"))
	{
		node->is_leaf = ft_atoi(ptr);
		while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
			ptr++;
		return (ptr + 1);
	}
	else if (!ft_strcmp(key, "floor"))
	{
		node->floor = ft_atof(ptr);
		while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
			ptr++;
		return (ft_strchr(ptr, ','));
	}
	else
		return (read_property_1(node, key, ptr));
}
