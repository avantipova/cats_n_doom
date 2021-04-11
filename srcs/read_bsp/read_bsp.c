/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bsp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:43:32 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 19:43:41 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	read_data(t_doom *doom, char *str)
{
	char	*ptr;

	ptr = str;
	ptr = ft_strchr(str, '{') + 1;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || \
				*ptr == '\n' || *ptr == '{' || *ptr == ',')
			ptr++;
		if (*ptr == '"')
		{
			ptr = read_data_property(doom, ptr + 1);
			if (!ptr)
				return ;
		}
		else if (*ptr == '}')
			break ;
	}
}

void	read_bsp(t_doom *doom, char *filename)
{
	int		fd;
	char	*read_str;

	read_str = malloc(262144);
	fd = open(filename, O_RDWR);
	if (fd < 0)
	{
		ft_putendl("Ошибка чтения файла");
		exit(-2);
	}
	read_str[read(fd, read_str, 262143)] = 0;
	close(fd);
	read_data(doom, read_str);
	free(read_str);
}

void	clear_bsp(t_bsp *node)
{
	free(node->vt_trs);
	if (node->is_leaf)
		return ;
	clear_bsp(node->front);
	clear_bsp(node->back);
	free(node->front);
	free(node->back);
}
