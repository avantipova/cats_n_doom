/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1_2_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 20:47:14 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/10 21:05:50 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	do_result(t_a_t_b *tatb, t_bsp *node, t_map *map, int i)
{
	do_vt_sec(tatb, node, map, i);
	do_uv(tatb, node, map, i);
	tatb->link->vt_trs[tatb->link->vt_trs_count] = tatb->new;
	(tatb->link->vt_trs_count)++;
	do_vt(tatb, node, map, i);
	do_uv_sec(tatb, node, map, i);
	tatb->link->vt_trs[tatb->link->vt_trs_count] = tatb->new;
	(tatb->link->vt_trs_count)++;
}

void	do_uv3_next(t_a_t_b *tatb, t_bsp *node, t_map *map, int i)
{
	tatb->vt = (t_vertex){
		node->walls[i].points[0].x, node->walls[i].points[0].y, \
								map->circuits[node->circuit].ceil};
	tatb->new.ids[0] = add_vt(map, tatb->vt);
	tatb->vt = (t_vertex){node->walls[i].points[1].x, node->walls[i].points[1].y, \
					map->circuits[node->circuit].floor};
	tatb->new.ids[1] = add_vt(map, tatb->vt);
	tatb->vt = (t_vertex){
		node->walls[i].points[1].x, node->walls[i].points[1].y, \
					map->circuits[node->circuit].ceil};
	tatb->new.ids[2] = add_vt(map, tatb->vt);
	tatb->vt = triangle_normal(map->vts[tatb->new.ids[2]], map->vts[tatb->new.ids[1]], \
					map->vts[tatb->new.ids[0]]);
	tatb->new.n_ids[0] = add_n(map, tatb->vt);
	tatb->new.n_ids[1] = tatb->new.n_ids[0];
	tatb->new.n_ids[2] = tatb->new.n_ids[0];
}
