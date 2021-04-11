/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_property.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:40:26 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 19:48:48 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

char	*first_condition(t_doom *doom, char *ptr)
{
	ptr = ft_strchr(ptr, '[') + 1;
	doom->scene.camera.position.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	doom->scene.camera.position.z = ft_atof(ptr);
	doom->start_pos = doom->scene.camera.position;
	return (ft_strchr(ptr, ']') + 1);
}

char	*second_condition(t_doom *doom, char *ptr)
{
	ptr = ft_strchr(ptr, '[') + 1;
	doom->aim.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	doom->aim.z = ft_atof(ptr);
	doom->aim.y = 0.0;
	return (ft_strchr(ptr, ']') + 1);
}

char	*read_data_property(t_doom *doom, char *str)
{
	char	key[32];
	char	*ptr;

	ft_strncpy(key, str, ft_strchr(str, '"') - str);
	key[ft_strchr(str, '"') - str] = 0;
	puts(key);
	ptr = ft_strchr(str, ':') + 1;
	if (!ft_strcmp(key, "player"))
		return (first_condition(doom, ptr));
	else if (!ft_strcmp(key, "aim"))
		return (second_condition(doom, ptr));
	else if (!ft_strcmp(key, "enemies"))
		return (read_enemies(doom, ptr));
	else if (!ft_strcmp(key, "tv"))
		return (read_tv(doom, ptr));
	else if (!ft_strcmp(key, "ammo"))
		return (read_ammo(doom, ptr));
	else if (!ft_strcmp(key, "aid"))
		return (read_aid(doom, ptr));
	else if (!ft_strcmp(key, "objects"))
		return (read_objects(doom, ptr));
	else if (!ft_strcmp(key, "bsp"))
		read_node(&doom->scene.level.root, ft_strchr(ptr, '{') + 1);
	return (NULL);
}
