/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:57:18 by ldeirdre          #+#    #+#             */
/*   Updated: 2021/05/10 21:05:55 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	do_uv_2(t_a_t_b *tatb, t_bsp *node, t_map *map, int i)
{
	tatb->uv = (t_vertex){
		node->trs[i].points[0].x * TEXTURE_SCALE, \
			node->trs[i].points[0].y * TEXTURE_SCALE, 0.0};
	tatb->new.uv_ids[0] = add_uv(map, tatb->uv);
	tatb->uv = (t_vertex){
		node->trs[i].points[1].x * TEXTURE_SCALE, \
			node->trs[i].points[1].y * TEXTURE_SCALE, 0.0};
	tatb->new.uv_ids[1] = add_uv(map, tatb->uv);
	tatb->uv = (t_vertex){
		node->trs[i].points[2].x * TEXTURE_SCALE, \
			node->trs[i].points[2].y * TEXTURE_SCALE, 0.0};
	tatb->new.uv_ids[2] = add_uv(map, tatb->uv);
}

void	do_uv_3(t_a_t_b *tatb, t_bsp *node, t_map *map, int i)
{
	tatb->uv = (t_vertex){
		0.0, map->circuits[node->circuit].floor * TEXTURE_SCALE, 0.0};
	tatb->new.uv_ids[0] = add_uv(map, tatb->uv);
	tatb->uv = (t_vertex){
		0.0, map->circuits[node->circuit].ceil * TEXTURE_SCALE, 0.0};
	tatb->new.uv_ids[1] = add_uv(map, tatb->uv);
	tatb->uv = (t_vertex){
		length(sub(node->walls[i].points[0], \
			node->walls[i].points[1])) * TEXTURE_SCALE, \
			map->circuits[node->circuit].ceil * TEXTURE_SCALE, 0.0};
	tatb->new.uv_ids[2] = add_uv(map, tatb->uv);
	tatb->new.type = TR_TYPE_WALL;
	node->vt_trs[node->vt_trs_count] = tatb->new;
	(node->vt_trs_count)++;
	do_uv3_next(tatb, node, map, i);
}

void	do_uv_4(t_a_t_b *tatb, t_bsp *node, t_map *map, int i)
{
	tatb->uv = (t_vertex){
		0.0, map->circuits[node->circuit].floor * TEXTURE_SCALE, 0.0};
	tatb->new.uv_ids[0] = add_uv(map, tatb->uv);
	tatb->uv = (t_vertex){
		length(sub(node->walls[i].points[0], \
			node->walls[i].points[1])) * TEXTURE_SCALE, \
			map->circuits[node->circuit].ceil * TEXTURE_SCALE, 0.0 };
	tatb->new.uv_ids[1] = add_uv(map, tatb->uv);
	tatb->uv = (t_vertex){length(sub(node->walls[i].points[0], \
			node->walls[i].points[1])) * TEXTURE_SCALE, \
			map->circuits[node->circuit].floor * TEXTURE_SCALE, 0.0};
	tatb->new.uv_ids[2] = add_uv(map, tatb->uv);
	tatb->new.type = TR_TYPE_WALL;
	node->vt_trs[node->vt_trs_count] = tatb->new;
	(node->vt_trs_count)++;
}

void	to_obj_format_uv_vt(t_bsp *node, t_map *map, t_a_t_b *tatb)
{
	int		i;

	i = 0;
	while (i < node->walls_count)
	{
		if (node->walls[i].type != WALL_TYPE_WALL)
		{
			i++;
			continue ;
		}
		do_vt_4(tatb, node, map, i);
		do_uv_3(tatb, node, map, i);
		do_uv_4(tatb, node, map, i);
		i++;
	}
}

void	to_obj_format(t_bsp *node, t_map *map)
{
	int		i;
	t_a_t_b	*tatb;

	i = 0;
	tatb = (t_a_t_b *)malloc(sizeof(t_a_t_b));
	node->vt_trs = malloc(sizeof(t_vt_tr) * 30000);
	node->vt_trs_count = 0;
	while (i < node->trs_count)
	{
		do_vt_2(tatb, node, map, i);
		do_uv_2(tatb, node, map, i);
		tatb->new.type = TR_TYPE_FLOOR;
		node->vt_trs[node->vt_trs_count] = tatb->new;
		(node->vt_trs_count)++;
		do_vt_3(tatb, node, map, i);
		do_uv_2(tatb, node, map, i);
		tatb->new.type = TR_TYPE_CEIL;
		node->vt_trs[node->vt_trs_count] = tatb->new;
		(node->vt_trs_count)++;
		i++;
	}
	to_obj_format_uv_vt(node, map, tatb);
}
