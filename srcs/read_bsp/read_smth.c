/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_smth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:33:37 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 19:52:24 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

char	*read_walls(t_bsp *node, char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == ',')
			ptr++;
		if (*ptr == '{')
		{
			ptr = add_wall(node, ptr + 1);
		}
		else if (*ptr == ']')
			break ;
	}
	return (ft_strchr(ptr, ']') + 1);
}

char	*read_vt_trs(t_bsp *node, char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == ',')
			ptr++;
		if (*ptr == '{')
		{
			ptr = add_vt_tr(node, ptr + 1);
		}
		else if (*ptr == ']')
			break ;
	}
	return (ft_strchr(ptr, ']') + 1);
}

char	*read_node(t_bsp *node, char *str)
{
	char	*ptr;

	node->walls_count = 0;
	node->vt_trs_count = 0;
	node->vt_trs = malloc(sizeof(t_vt_tr) * 1000);
	ptr = str;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || \
					*ptr == '\n' || *ptr == '{' || *ptr == ',')
			ptr++;
		if (*ptr == '"')
		{
			ptr = read_property(node, ptr + 1);
		}
		else if (*ptr == '}')
			break ;
	}
	return (ft_strchr(ptr, '}') + 1);
}

char	*read_enemies(t_doom *doom, char *ptr)
{
	doom->enemies_count = 0;
	ptr = ft_strchr(ptr, '[') + 1;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == ',')
			ptr++;
		if (*ptr == '[')
		{
			ptr = add_enemy(doom, ptr + 1);
		}
		else if (*ptr == ']')
			break ;
	}
	return (ft_strchr(ptr, ']') + 1);
}
