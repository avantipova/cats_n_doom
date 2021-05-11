/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_json_3_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 22:13:45 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/11 22:01:38 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	check_objects_while(t_map_editor *ed, int fd)
{
	char	str[64];
	int		i;

	i = 0;
	while (i < ed->objects_count)
	{
		ft_putstr_fd("{\n\t\t\t\"index\":", fd);
		if (ed->objects[i].exir == 1)
			ed->objects[i].index = 8;
		else
			ed->objects[i].index = (i + 8) % 8;
		itoa(ed->objects[i].index, str);
		ft_putstr_fd(str, fd);
		ft_putstr_fd(", ", fd);
		ft_putstr_fd("\n\t\t\t\"pos\": [", fd);
		ftoa(ed->objects[i].pos.x, 8, str);
		ft_putstr_fd(str, fd);
		ft_putstr_fd(", ", fd);
		ftoa(ed->objects[i].pos.y, 8, str);
		ft_putstr_fd(str, fd);
		ft_putstr_fd("]}", fd);
		if (i < ed->objects_count - 1)
			ft_putstr_fd(",", fd);
		i++;
	}
}
