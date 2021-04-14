/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:27:45 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 16:23:04 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static char	*check_points(char *ptr, t_bsp *node)
{
	ptr = ft_strchr(ptr, '[') + 1;
	ptr = ft_strchr(ptr, '[') + 1;
	node->walls[node->walls_count].points[0].x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	node->walls[node->walls_count].points[0].y = ft_atof(ptr);
	ptr = ft_strchr(ptr, '[') + 1;
	node->walls[node->walls_count].points[1].x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	node->walls[node->walls_count].points[1].y = ft_atof(ptr);
	ptr = ft_strchr(ptr, ']') + 1;
	ptr = ft_strchr(ptr, ']') + 1;
	return (ptr);
}

static char	*add_wall_2(char *ptr, t_bsp *node, char *key)
{
	if (!ft_strcmp(key, "points"))
	{
		ptr = check_points(ptr, node);
	}
	else if (!ft_strcmp(key, "normal"))
	{
		ptr = ft_strchr(ptr, '[') + 1;
		node->walls[node->walls_count].normal.x = ft_atof(ptr);
		ptr = ft_strchr(ptr, ',') + 1;
		node->walls[node->walls_count].normal.y = ft_atof(ptr);
		ptr = ft_strchr(ptr, ']') + 1;
	}
	else if (!ft_strcmp(key, "type"))
	{
		node->walls[node->walls_count].type = ft_atoi(ptr);
		ptr = ft_strchr(ptr, ',') + 1;
	}
	return (ptr);
}

char	*add_wall(t_bsp *node, char *str)
{
	char	key[32];
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || \
						*ptr == '\n' || *ptr == '{' || *ptr == ',')
			ptr++;
		if (*ptr == '"')
		{
			ptr++;
			ft_strncpy(key, ptr, ft_strchr(ptr, '"') - ptr);
			key[ft_strchr(ptr, '"') - ptr] = 0;
			ptr = ft_strchr(ptr, ':') + 1;
			ptr = add_wall_2(ptr, node, key);
		}
		else if (*ptr == '}')
			break ;
	}
	(node->walls_count)++;
	return (ft_strchr(ptr, '}') + 1);
}
