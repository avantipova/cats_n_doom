#include "duke.h"

void	get_points(t_model *model, char *file_name)
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
		if (line[0] == 'v' && line[1] == ' ')
		{
			model->vertexes[i] = read_coords(line);
			model->vertexes_count++;
			i++;
		}
		free(line);
	}
	close(fd);
}

t_triangle	generate_polygon(char *line, t_model *model, t_vertex *normals)
{
	t_triangle	ret;
	char		*tmp;
	int			number;

	tmp = ft_strchr(line, ' ') + 1;
	number = ft_atoi(tmp);
	ret.indexes[0] = number - 1;
	tmp = ft_strchr(tmp, '/') + 1;
	number = ft_atoi(tmp);
	ret.uvs[0] = model->uvs[number - 1];
	tmp = ft_strchr(tmp, ' ') + 1;
	number = ft_atoi(tmp);
	ret.indexes[1] = number - 1;
	tmp = ft_strchr(tmp, '/') + 1;
	number = ft_atoi(tmp);
	ret.uvs[1] = model->uvs[number - 1];
	tmp = ft_strchr(tmp, ' ') + 1;
	number = ft_atoi(tmp);
	ret.indexes[2] = number - 1;
	tmp = ft_strchr(tmp, '/') + 1;
	ret.uvs[2] = model->uvs[ft_atoi(tmp) - 1];
	tmp = ft_strchr(tmp, '/') + 1;
	ret.normal = normals[ft_atoi(tmp) - 1];
	ret.tex = model->new_tex[0];
	return (ret);
}

void	get_polygons(t_model *model, char *file_name, t_vertex *normals)
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
		if (line[0] == 'f' && line[1] == ' ')
		{
			model->triangles[i] = generate_polygon(line, model, normals);
			model->triangles_count++;
			i++;
		}
		free(line);
	}
	close(fd);
}

void	read_obj(t_model *model, char *file_name)
{
	model->normals_count = 0;
	model->normals = malloc(sizeof(t_vertex) * 3000);
	if (!model->normals)
		exit(-2);
	model->vertexes_count = 0;
	get_points(model, file_name);
	model->uvs_count = 0;
	get_uvss(model, file_name);
	get_normals(model->normals, &model->normals_count, file_name);
	model->triangles_count = 0;
	get_polygons(model, file_name, model->normals);
}
