/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:48:14 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 21:35:29 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static t_enemy	check_enemy_1(t_model enemy_model, \
													t_vertex pos, float beta)
{
	t_enemy	enemy;

	enemy_model.triangles = malloc(sizeof(t_triangle) * 2);
	enemy_model.triangles[0].indexes[0] = 0;
	enemy_model.triangles[0].indexes[1] = 1;
	enemy_model.triangles[0].indexes[2] = 2;
	enemy_model.triangles[1].indexes[0] = 0;
	enemy_model.triangles[1].indexes[1] = 2;
	enemy_model.triangles[1].indexes[2] = 3;
	enemy_model.triangles[0].normal = (t_vertex){0.0, 0.0, 1.0};
	enemy_model.triangles[1].normal = (t_vertex){0.0, 0.0, 1.0};
	enemy_model.triangles[0].uvs[0] = (t_point){0.0, 1.0, 0.0};
	enemy_model.triangles[0].uvs[1] = (t_point){0.0, 0.0, 0.0};
	enemy_model.triangles[0].uvs[2] = (t_point){1.0, 0.0, 0.0};
	enemy_model.triangles[1].uvs[0] = (t_point){0.0, 1.0, 0.0};
	enemy_model.triangles[1].uvs[1] = (t_point){1.0, 0.0, 0.0};
	enemy_model.triangles[1].uvs[2] = (t_point){1.0, 1.0, 0.0};
	enemy.sprite.instance.model = enemy_model;
	enemy.sprite.instance.scale = 1.0;
	enemy.sprite.instance.position = pos;
	enemy.sprite.instance.orientation = make_oy_rot_matrix(0.0);
	enemy.beta = beta;
	return (enemy);
}

static void	check_enemy_2(t_enemy *enemy)
{
	enemy->walking_anims[0] = load_anim(ASSETS_FOLDER_NAME \
					"/textures/animm/front/", 4.0, 0xff00ffff);
	enemy->walking_anims[1] = load_anim(ASSETS_FOLDER_NAME \
					"/textures/animm/front-left/", 4.0, 0xff00ffff);
	enemy->walking_anims[2] = load_anim(ASSETS_FOLDER_NAME \
					"/textures/animm/left/", 4.0, 0xff00ffff);
	enemy->walking_anims[3] = load_anim(ASSETS_FOLDER_NAME \
					"/textures/animm/back-left/", 4.0, 0xff00ffff);
	enemy->walking_anims[4] = load_anim(ASSETS_FOLDER_NAME \
					"/textures/animm/back/", 4.0, 0xff00ffff);
	enemy->walking_anims[5] = load_anim(ASSETS_FOLDER_NAME \
					"/textures/animm/back-right/", 4.0, 0xff00ffff);
	enemy->walking_anims[6] = load_anim(ASSETS_FOLDER_NAME \
					"/textures/animm/right/", 4.0, 0xff00ffff);
	enemy->walking_anims[7] = load_anim(ASSETS_FOLDER_NAME \
					"/textures/animm/front-right/", 4.0, 0xff00ffff);
	enemy->attak_anim = load_anim(ASSETS_FOLDER_NAME \
								"/textures/attak/", 4.0, 0xff00ffff);
	enemy->damage_anim = load_anim(ASSETS_FOLDER_NAME \
								 "/textures/damage/", 4.0, 0xff00ffff);
	enemy->death_anim = load_anim(ASSETS_FOLDER_NAME \
								"/textures/death/", 4.0, 0xff00ffff);
	enemy->sprite.instance.model.anim = &enemy->walking_anims[0];
	enemy->sprite.instance.model.new_tex[0] = \
					enemy->sprite.instance.model.anim->frames[0];
}

t_enemy	create_enemy(t_vertex pos, float beta)
{
	t_enemy	enemy;
	t_model	enemy_model;

	enemy_model.bounds_center = (t_vertex){0.0, 0.0, 0.0};
	enemy_model.bounds_radius = 2.0;
	enemy_model.triangles_count = 2;
	enemy_model.vertexes_count = 4;
	enemy_model.vertexes = malloc(sizeof(t_vertex) * 4);
	enemy_model.vertexes[0] = (t_vertex){-1.0, -1.0, 0.0};
	enemy_model.vertexes[1] = (t_vertex){-1.0, 1.0, 0.0};
	enemy_model.vertexes[2] = (t_vertex){1.0, 1.0, 0.0};
	enemy_model.vertexes[3] = (t_vertex){1.0, -1.0, 0.0};
	enemy = check_enemy_1(enemy_model, pos, beta);
	check_enemy_2(&enemy);
	enemy.damaged = 0;
	enemy.in_attak = 0;
	enemy.start_pos = pos;
	enemy.health = 100;
	return (enemy);
}
