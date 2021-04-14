/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullets_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:23:02 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 20:23:28 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	bullets_init(t_doom *doom)
{
	t_model bullet_model;
	t_bullet bullet;
	int i;
	
	bullet_model.bounds_center = (t_vertex) {0.0,0.0,0.0};
	bullet_model.bounds_radius = 2.0;
	bullet_model.triangles_count = 2;
	bullet_model.vertexes_count = 4;

	bullet_model.vertexes = malloc(sizeof(t_vertex) * 4);

	bullet_model.vertexes[0] = (t_vertex) {-0.1,-0.1,0.0};
	bullet_model.vertexes[1] = (t_vertex) {-0.1,0.1,0.0};
	bullet_model.vertexes[2] = (t_vertex) {0.1,0.1,0.0};
	bullet_model.vertexes[3] = (t_vertex) {0.1,-0.1,0.0};

	bullet_model.triangles = malloc(sizeof(t_triangle) * 2);
	bullet_model.triangles[0].indexes[0] = 0;
	bullet_model.triangles[0].indexes[1] = 1;
	bullet_model.triangles[0].indexes[2] = 2;

	bullet_model.triangles[1].indexes[0] = 0;
	bullet_model.triangles[1].indexes[1] = 2;
	bullet_model.triangles[1].indexes[2] = 3;

	bullet_model.triangles[0].normal = (t_vertex) {0.0,0.0,1.0};
	bullet_model.triangles[1].normal = (t_vertex) {0.0,0.0,1.0};

	bullet_model.triangles[0].uvs[0] = (t_point) {0.0, 1.0,0.0};
	bullet_model.triangles[0].uvs[1] = (t_point) {0.0, 0.0,0.0};
	bullet_model.triangles[0].uvs[2] = (t_point) {1.0, 0.0,0.0};

	bullet_model.triangles[1].uvs[0] = (t_point) {0.0, 1.0,0.0};
	bullet_model.triangles[1].uvs[1] = (t_point) {1.0, 0.0,0.0};
	bullet_model.triangles[1].uvs[2] = (t_point) {1.0, 1.0,0.0};

	bullet_model.new_tex[0] = create_texture(ASSETS_FOLDER_NAME "/textures/bullet.bmp", 0xfffaff08);
	bullet_model.new_tex[0]->flags = 0xfffaff08;

	bullet_model.anim = NULL;
	
	bullet.sprite.instance.model = bullet_model;
	bullet.sprite.instance.scale = 1.0;
	bullet.enable = 0;

	bullet.sprite.instance.orientation = make_oy_rot_matrix(0.0);

	i = 0;
	while (i < 40)
	{
		doom->bullets[i] = bullet;
		i++;
	}
}
