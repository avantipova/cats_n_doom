#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "archiver.h"
#include "duke.h"


void	creat_folders_by_filepath(char *path)
{
	char folderpath[64];
	char *ptr;

	ptr = path;
	while (1)
	{
		ptr = ft_strchr(ptr, '/');
		if (!ptr)
			break ;
		ptr += 1;
		ft_bzero(folderpath, 64);
		ft_memcpy(folderpath, path, ptr - path);
		mkdir(folderpath, S_IRWXU);	
	}
}

void	dearchivate_file(t_archiver *arc, char *filename)
{
	char filename_with_assets_folder[128];

	ft_strcpy(filename_with_assets_folder, ASSETS_FOLDER_NAME "/");
	ft_memcpy(filename, arc->archive + arc->list_index, 64);
	ft_strcat(filename_with_assets_folder, filename);

	arc->list_index += 64;
	arc->file_index = ft_atoi(arc->archive + arc->list_index);
	arc->list_index += 10;
	arc->file_length = ft_atoi(arc->archive + arc->list_index);
	arc->list_index += 10;

	creat_folders_by_filepath(filename_with_assets_folder);

	arc->file_fd = open(filename_with_assets_folder,
				O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);////////
		
	write(arc->file_fd, arc->archive + arc->file_index, arc->file_length);
	close(arc->file_fd);
}

void	dearchivate(char *archivename)
{
	t_archiver	arc;
	int			i;
	char		filename[64];
	int			files_count;

	arc.archive = malloc(99999999);///////
	arc.archive_fd = open(archivename, O_RDONLY);///////
	read(arc.archive_fd, arc.archive, 99999999);
	i = 0;
	files_count = ft_atoi(arc.archive);
	arc.list_index = 10;

	while (i < files_count)
	{
		dearchivate_file(&arc, filename);
		i++;
	}

	free(arc.archive);
	close(arc.archive_fd);
}
