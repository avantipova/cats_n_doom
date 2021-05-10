/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus_minus_enter_keys.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:12:35 by Chorange          #+#    #+#             */
/*   Updated: 2021/05/10 21:40:32 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "archiver.h"

int	get_files_count(int fd)
{
	int		count;
	char	*line;
	int		flag;

	count = 0;
	flag = 1;
	line = NULL;
	while (flag)
	{
		flag = get_next_line(fd, &line);
		if (flag == -1)
			exit(-2);
		if (line && ft_strlen(line))
			count++;
		if (flag > 0)
		{
			free(line);
			line = NULL;
		}
	}
	ft_putnbr(count);
	return (count);
}

void	write_filenames_to_list(t_archive_files_list *list, int fd)
{
	int		i;
	char	*line;
	int		flag;

	i = 0;
	flag = 1;
	line = NULL;
	while (flag)
	{
		flag = get_next_line(fd, &line);
		if (flag == -1)
			exit(-2);
		if (line && ft_strlen(line))
		{
			ft_strcpy(list->files[i], line);
			ft_putendl(list->files[i]);
			i++;
		}
		if (flag > 0)
		{
			free(line);
			line = NULL;
		}
	}
}

void	archive_files_list_init(t_archive_files_list *list)
{
	int		fd;
	int		i;

	i = 0;
	fd = open("files_list", O_RDONLY);
	list->files_count = get_files_count(fd);
	list->files = (char **)malloc(sizeof(char *) * list->files_count);
	while (i < list->files_count)
	{
		list->files[i] = (char *)malloc(64);
		i++;
	}
	close(fd);
	fd = open("files_list", O_RDONLY);
	write_filenames_to_list(list, fd);
	close(fd);
}

void	get_archive_name(char **archive_name)
{
	int		fd;

	while (1)
	{
		get_next_line(0, archive_name);
		fd = open(*archive_name, O_RDONLY);
		if (fd > -1)
		{
			ft_putendl("Файл уже существует, введите иное имя");
			free(*archive_name);
			*archive_name = NULL;
			close(fd);
		}
		else
			break ;
	}
}

void	save_archive(t_map_editor *ed)
{
	t_archive_files_list	list;
	char					*archive_name;

	archive_name = NULL;
	archive_files_list_init(&list);
	export_map(ed);
	save_json(&ed->root, ed);
	set_hash();
	ft_putendl("Введите название для файла и нажмите Enter");
	get_archive_name(&archive_name);
	archivate(&list, archive_name);
	if (archive_name)
		free(archive_name);
	remove("geometry.obj");
	remove("data.json");
	free_archive_files_list(&list);
}
