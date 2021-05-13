#ifndef ARCHIVER_H
# define ARCHIVER_H

typedef struct s_archiver
{
	int			archive_fd;
	int			file_fd;
	int			list_index;
	int			file_index;
	int			file_length;
	char		*archive;
	char		*file;
}				t_archiver;

typedef struct s_archive_files_list
{
	int			files_count;
	char		**files;
}				t_archive_files_list;

void			archivate(t_archive_files_list *files_list, char *archive_name);

void			dearchivate(char *archivename);
void			free_archive_files_list(t_archive_files_list *files_list);

#endif
