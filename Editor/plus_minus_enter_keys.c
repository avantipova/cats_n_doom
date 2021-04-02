/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus_minus_enter_keys.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Chorange <Chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:12:35 by Chorange          #+#    #+#             */
/*   Updated: 2021/04/03 02:26:42 by Chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "archiver.h"

int			get_files_count(int fd)
{
	int count;
	char *line;
	int flag;

	count = 0;
	flag = 1;
	line = NULL;
	while (flag)
	{
		flag = get_next_line(fd, &line);
		if (flag == -1)
			exit(-2);///////////////сообщение об ошибке
		
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

void		write_filenames_to_list(t_archive_files_list *list, int fd)
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
			exit(-2);///////////////сообщение об ошибке
		
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

void		archive_files_list_init(t_archive_files_list *list)
{
	int fd;
	int i;

	fd = open("files_list", O_RDONLY);////////////

	list->files_count = get_files_count(fd);
	list->files = (char **)malloc(sizeof(char* ) * list->files_count);///////
	i = 0;
	while (i < list->files_count)
	{
		list->files[i] = (char *)malloc(64);/////////
		i++;
	}
	close(fd);
	fd = open("files_list", O_RDONLY);////////////
	write_filenames_to_list(list, fd);

	close(fd);
}

void			get_archive_name(char **archive_name)
{
	int fd;

	while (1)
	{
		get_next_line(0, archive_name);///////
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

void			save_archive(t_map_editor *ed)
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

void			key_enter_down(t_map_editor *ed)
{
	ed->step++;
	if (ed->step == STEP_2_FLOOR)
	{
		bsp_compile(ed);
		ed->mode = RENDER_MODE_WALLS;
	}
	else if (ed->step == STEP_4_TEXTURES)
	{
		ed->edit_wall_tex = 1;
		ed->edit_floor_tex = 0;
		ed->edit_ceil_tex = 0;
	}
	else if (ed->step == STEP_12_SAVE)
	{
		save_archive(ed);
		ed->mode = RENDER_MODE_TRS;
	}
	write_instructions(ed);
}

static void		key_minus_down_2(t_map_editor *ed)
{
	if (ed->step == STEP_3_CEIL)
	{
		ed->map.circuits[ed->map.selected_circuit].ceil -= 0.1;
		write_ceil_height(ed);
	}
	if (ed->step == STEP_2_FLOOR)
	{
		ed->map.circuits[ed->map.selected_circuit].floor -= 0.1;
		write_floor_height(ed);
	}
	if (ed->edit_floor_tex && ed->step == STEP_4_TEXTURES)
	{
		ed->map.circuits[ed->map.selected_circuit].floor_tex -= 1;
		if (ed->map.circuits[ed->map.selected_circuit].floor_tex < 0)
			ed->map.circuits[ed->map.selected_circuit].floor_tex = 5;
		write_floor_tex(ed);
	}
	if (ed->edit_ceil_tex && ed->step == STEP_4_TEXTURES)
	{
		ed->map.circuits[ed->map.selected_circuit].ceil_tex -= 1;
		if (ed->map.circuits[ed->map.selected_circuit].ceil_tex < 0)
			ed->map.circuits[ed->map.selected_circuit].ceil_tex = 5;
		write_ceil_tex(ed);
	}
}

void			key_minus_down(t_map_editor *ed)
{
	key_minus_down_2(ed);
	if (ed->edit_wall_tex && ed->step == STEP_4_TEXTURES)
	{
		ed->map.circuits[ed->map.selected_circuit].wall_tex -= 1;
		if (ed->map.circuits[ed->map.selected_circuit].wall_tex < 0)
			ed->map.circuits[ed->map.selected_circuit].wall_tex = 5;
		write_wall_tex(ed);
	}
	if (ed->step == STEP_10_OBJECTS)
	{
		ed->curr_object -= 1;
		if (ed->curr_object < 0)
			ed->curr_object = 3;
		write_object_num(ed);
	}
	if (ed->step == STEP_9_DECOR)
	{
		ed->tv_beta -= 5.0;
	}
}

static void	key_plus_down_2(t_map_editor *ed)
{
	if (ed->edit_ceil_tex && ed->step == STEP_4_TEXTURES)
	{
		ed->map.circuits[ed->map.selected_circuit].ceil_tex += 1;
		if (ed->map.circuits[ed->map.selected_circuit].ceil_tex > 5)
			ed->map.circuits[ed->map.selected_circuit].ceil_tex = 0;
		write_ceil_tex(ed);
	}
	if (ed->edit_wall_tex && ed->step == STEP_4_TEXTURES)
	{
		ed->map.circuits[ed->map.selected_circuit].wall_tex += 1;
		if (ed->map.circuits[ed->map.selected_circuit].wall_tex > 5)
			ed->map.circuits[ed->map.selected_circuit].wall_tex = 0;
		write_wall_tex(ed);
	}
	if (ed->step == STEP_10_OBJECTS)
	{
		ed->curr_object += 1;
		if (ed->curr_object > 3)
			ed->curr_object = 0;
		write_object_num(ed);
	}
	if (ed->step == STEP_9_DECOR)
		ed->tv_beta += 10.0;
}

void			key_plus_down(t_map_editor *ed)
{
	key_plus_down_2(ed);
	if (ed->step == STEP_3_CEIL)
	{
		ed->map.circuits[ed->map.selected_circuit].ceil += 0.1;
		write_ceil_height(ed);
	}
	if (ed->step == STEP_2_FLOOR)
	{
		ed->map.circuits[ed->map.selected_circuit].floor += 0.1;
		write_floor_height(ed);
	}
	if (ed->edit_floor_tex && ed->step == STEP_4_TEXTURES)
	{
		ed->map.circuits[ed->map.selected_circuit].floor_tex += 1;
		if (ed->map.circuits[ed->map.selected_circuit].floor_tex > 5)
			ed->map.circuits[ed->map.selected_circuit].floor_tex = 0;
		write_floor_tex(ed);
	}
}
