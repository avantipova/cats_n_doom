/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:51:17 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 17:52:09 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	check_correct_loop(t_doom *doom, float *floor, float *ceil)
{
	int		i;

	i = -1;
	while (++i < 40)
	{
		if (doom->aid[i].enable)
		{
			get_floor_seil_traversal(&doom->scene.level.root, \
				(t_vertex){doom->aid[i].sprite.instance.position.x, \
				doom->aid[i].sprite.instance.position.z, 0.0}, floor, ceil);
			doom->aid[i].sprite.instance.position.y = *floor + 0.3;
		}
		if (doom->ammo[i].enable)
		{
			get_floor_seil_traversal(&doom->scene.level.root, \
				(t_vertex){doom->ammo[i].sprite.instance.position.x, \
				doom->ammo[i].sprite.instance.position.z, 0.0}, floor, ceil);
			doom->ammo[i].sprite.instance.position.y = *floor + 0.3;
		}
	}
}

void	correct_objects_height(t_doom *doom)
{	
	int		i;
	float	floor;
	float	ceil;

	check_correct_loop(doom, &floor, &ceil);
	i = -1;
	while (++i < doom->objects_count)
		get_floor_seil_traversal(&doom->scene.level.root, \
				(t_vertex){doom->objects[i].sprite.instance.position.x, \
			doom->objects[i].sprite.instance.position.z, 0.0}, &floor, &ceil);
	doom->objects[i].sprite.instance.position.y = floor + 0.8;
	get_floor_seil_traversal(&doom->scene.level.root, \
				(t_vertex){doom->tv.sprite.instance.position.x, \
				doom->tv.sprite.instance.position.z, 0.0}, &floor, &ceil);
	doom->tv.sprite.instance.position.y = floor + 1.5;
}

static void	level_init_2(t_scene *scene)
{
	scene->level.instance.position = (t_vertex){0, 0, 10};
	scene->level.instance.clipped = malloc(sizeof(t_vertex) * 10);
	scene->level.instance.scale = 1.0;
	scene->level.instance.orientation = make_oy_rot_matrix(0.0);
	scene->level.instance.scale = 1.0;
	scene->level.instance.position = (t_vertex){0, 0, 0};
}

void	level_init(t_doom *doom, char *foldername)
{
	t_scene	*scene;
	char	path[1024];

	scene = &doom->scene;
	scene->z_buffer = create_z_buffer();
	scene->camera.orientation = make_oy_rot_matrix(360.0);
	scene->camera.position = (t_vertex){0, 0, -2};
	ft_strcpy(path, foldername);
	ft_strcat(path, "/data.json");
	read_bsp(doom, path);
	correct_objects_height(doom);
	scene->level.instance.model.vertexes = malloc(sizeof(t_vertex) * 30000);
	scene->level.instance.model.vertexes_count = 0;
	scene->level.instance.model.triangles = malloc(sizeof(t_triangle) * 30000);
	scene->level.instance.model.triangles_count = 0;
	scene->level.instance.model.uvs = malloc(sizeof(t_point) * 30000);
	scene->level.instance.model.uvs_count = 0;
	scene->level.instance.model.bounds_center = (t_vertex){0, 0, 0};
	scene->level.instance.model.bounds_radius = 100;
	ft_strcpy(path, foldername);
	ft_strcat(path, "/geometry.obj");
	read_obj(&scene->level.instance.model, path);
	level_init_2(scene);
}
