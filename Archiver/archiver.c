#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "archiver.h"
#include "duke.h"

/*
	числа пишем символьно для лучшей читаемости

	первые 10 байт - количество позиций в оглавлении (количество файлов считай)

	дальше идут сами позиции оглавления: на каждую:
		64 символа на полный путь файла этой позиции ("textures/sprites/1.bmp"),
		10 сиволов на индекс певого байта этого файла в нашем архиве
		10 на количество байт для этого файла

		итого 84 байта на каждую позицию оглавления

		и потом идут сами файлики, побайтово записанные в строчечку
*/

void	free_archive_files_list(t_archive_files_list *files_list)
{
	int	i;

	i = 0;
	while (i < files_list->files_count)
	{
		free(files_list->files[i]);
		i++;
	}
	free(files_list->files);
}

void	archivate_file(int file_index, t_archiver *arc, char *tmp,
				t_archive_files_list *files_list)
{
	arc->file_fd = open(files_list->files[file_index], O_RDONLY);
	if (arc->file_fd < 0)
	{
		ft_putstr("Ошибка открытия файла ");
		ft_putendl(files_list->files[file_index]);
	}
	arc->file_length = read(arc->file_fd, arc->file, 9999999);
	if (arc->file_length < 0)
	{
		ft_putstr("Ошибка чтения файла ");
		ft_putendl(files_list->files[file_index]);
	}
	ft_strcpy(arc->archive + arc->list_index, files_list->files[file_index]);
	arc->list_index += 64;
	ft_strcpy(arc->archive + arc->list_index, itoa(arc->file_index, tmp));
	arc->list_index += 10;
	ft_strcpy(arc->archive + arc->list_index, itoa(arc->file_length, tmp));
	arc->list_index += 10;
	ft_memcpy(arc->archive + arc->file_index, arc->file, arc->file_length);
	arc->file_index += arc->file_length;
	close(arc->file_fd);
}

void	archivate(t_archive_files_list *files_list, char *archive_name)
{
	t_archiver	arc;
	char		tmp[64];
	int			i;

	arc.file = malloc(99999999);
	arc.archive = malloc(999999999);
	ft_bzero(arc.archive, 999999999);
	arc.list_index = 0;
	arc.file_index = 84 * files_list->files_count + 10;
	i = 0;
	ft_strcpy(arc.archive, itoa(files_list->files_count, tmp));
	arc.list_index += 10;
	while (i < files_list->files_count)
	{
		archivate_file(i, &arc, tmp, files_list);
		i++;
	}
	arc.archive_fd = open(archive_name, O_RDWR | O_CREAT, S_IRWXU);
	write(arc.archive_fd, arc.archive, arc.file_index);
	close(arc.archive_fd);
	free(arc.archive);
	free(arc.file);
}
