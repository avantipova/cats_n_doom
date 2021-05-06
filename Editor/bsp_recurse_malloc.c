/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_recurse_malloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:29:57 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/06 15:19:35 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	bsp_recurse_malloc(t_req_s *s, t_bsp *bsp, t_circuit *circuits,
			int circuits_count)
{
	s->front = malloc(sizeof(t_circuit) * circuits_count);
	s->back = malloc(sizeof(t_circuit) * circuits_count);
	if (s->front == NULL || s->back == NULL)
		exit(-2);
	ft_bzero(s->front, sizeof(t_circuit) * circuits_count);
	ft_bzero(s->back, sizeof(t_circuit) * circuits_count);
	bsp->is_leaf = 0;
	bsp->walls_count = 0;
	bsp->normal = circuits[s->cutter_cir].walls[s->cutter_wall].normal;
	bsp->back = malloc(sizeof(t_bsp));
	bsp->front = malloc(sizeof(t_bsp));
	if (bsp->front == NULL || bsp->back == NULL)
		exit(-2);
}
