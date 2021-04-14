/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_smth_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:38:54 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 16:01:57 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

char	*read_objects(t_doom *doom, char *ptr)
{
	doom->objects_count = 0;
	ptr = ft_strchr(ptr, '[') + 1;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == ',')
			ptr++;
		if (*ptr == '{')
		{
			ptr = add_object_d(doom, ptr + 1);
		}
		else if (*ptr == ']')
			break ;
	}
	return (ft_strchr(ptr, ']') + 1);
}

char	*read_tv(t_doom *doom, char *ptr)
{
	ptr = ft_strchr(ptr, '[') + 1;
	doom->tv.sprite.instance.position.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	doom->tv.sprite.instance.position.z = ft_atof(ptr);
	ptr = ft_strchr(ptr, ':') + 1;
	doom->tv.sprite.instance.position.y = 0.0;
	doom->tv.beta = ft_atof(ptr);
	create_tv(doom);
	return (ft_strchr(ptr, '}') + 1);
}

char	*read_ammo(t_doom *doom, char *ptr)
{
	int	ammo_count;

	ammo_count = 0;
	ptr = ft_strchr(ptr, '[') + 1;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == ',')
			ptr++;
		if (*ptr == '[')
		{
			ptr = add_ammo_d(doom, ptr + 1, &ammo_count);
		}
		else if (*ptr == ']')
			break ;
	}
	return (ft_strchr(ptr, ']') + 1);
}

char	*read_aid(t_doom *doom, char *ptr)
{
	int	aid_count;

	aid_count = 0;
	ptr = ft_strchr(ptr, '[') + 1;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == ',')
			ptr++;
		if (*ptr == '[')
		{
			ptr = add_aid_d(doom, ptr + 1, &aid_count);
		}
		else if (*ptr == ']')
			break ;
	}
	return (ft_strchr(ptr, ']') + 1);
}
