/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_gnl_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 20:45:00 by mjoss             #+#    #+#             */
/*   Updated: 2021/05/12 23:30:23 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strplus(char **str, size_t add)
{
	char	*tmp;
	size_t	len;

	tmp = ft_strdup(*str);
	len = ft_strlen(tmp);
	free(*str);
	*str = ft_strnew(len + add);
	ft_strncpy(*str, tmp, len);
	ft_strdel(&tmp);
	return (1);
}

int	val_file(int f, char **line, int ret)
{
	if (f < 0 || line == NULL || ret < 0)
		return (-1);
	return (0);
}

int	loop(t_list *curr, char *buf, int fd)
{
	int	ret;

	while (curr->read_bytes)
	{
		buf[curr->read_bytes] = '\0';
		ret = ft_strplus((char **)(&curr->content), curr->read_bytes);
		if (!ret)
			return (-1);
		ft_strncat((char *)curr->content, buf, curr->read_bytes);
		if (ft_strchr(buf, '\n'))
			break ;
		curr->read_bytes = read(fd, buf, BUFF_SIZE);
	}
	return (0);
}
