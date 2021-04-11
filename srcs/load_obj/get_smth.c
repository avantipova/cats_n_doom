/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_smth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:41:43 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 18:44:49 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

t_vertex	read_coords(char *line)
{
	t_vertex	ret;
	char		*tmp;

	tmp = ft_strchr(line, ' ') + 1;
	ret.x = atof(tmp);
	tmp = ft_strchr(tmp, ' ') + 1;
	ret.y = atof(tmp);
	tmp = ft_strchr(tmp, ' ') + 1;
	ret.z = atof(tmp);
	return (ret);
}

t_point	read_uvs(char *line)
{
	t_point	ret;
	char	*tmp;

	tmp = ft_strchr(line, ' ') + 1;
	ret.x = atof(tmp);
	tmp = ft_strchr(tmp, ' ') + 1;
	ret.y = atof(tmp);
	return (ret);
}

void	get_normals(t_vertex *normals, int *count, char *file_name)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(-2);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == 'n')
		{
			normals[i] = read_coords(line);
			(*count)++;
			i++;
		}
		free(line);
	}
	close(fd);
}

void	get_uvss(t_model *model, char *file_name)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(-2);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == 't')
		{
			model->uvs[i] = read_uvs(line);
			model->uvs_count++;
			i++;
		}
		free(line);
	}
	close(fd);
}
