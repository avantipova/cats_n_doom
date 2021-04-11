/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_smth_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:30:03 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 19:54:38 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

char	*add_enemy(t_doom *doom, char *ptr)
{
	t_vertex	pos;

	pos.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	pos.z = ft_atof(ptr);
	doom->enemies[doom->enemies_count] = create_enemy(pos, 0.0);
	doom->enemies_count++;
	return (ft_strchr(ptr, ']') + 1);
}

char	*add_object(t_doom *doom, char *ptr)
{
	t_vertex	pos;
	int			index;

	ptr = ft_strchr(ptr, ':') + 1;
	index = ft_atoi(ptr);
	ptr = ft_strchr(ptr, '[') + 1;
	pos.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	pos.z = ft_atof(ptr);
	doom->objects[doom->objects_count] = create_object(pos, index);
	doom->objects_count++;
	return (ft_strchr(ptr, '}') + 1);
}

char	*add_ammo(t_doom *doom, char *ptr, int *ammo_count)
{
	t_vertex	pos;

	pos.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	pos.z = ft_atof(ptr);
	doom->ammo[*ammo_count].enable = 1;
	doom->ammo[*ammo_count].sprite.instance.position = pos;
	doom->ammo[*ammo_count].start_enable = 1;
	(*ammo_count)++;
	return (ft_strchr(ptr, ']') + 1);
}

char	*add_aid(t_doom *doom, char *ptr, int *aid_count)
{
	t_vertex	pos;

	pos.x = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',') + 1;
	pos.z = ft_atof(ptr);
	doom->aid[*aid_count].enable = 1;
	doom->aid[*aid_count].sprite.instance.position = pos;
	doom->aid[*aid_count].start_enable = 1;
	(*aid_count)++;
	return (ft_strchr(ptr, ']') + 1);
}
