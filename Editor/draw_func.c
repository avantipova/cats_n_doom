/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:36:03 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/06 16:38:44 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	check_sign_x(t_int_v *f, t_int_v *sign, t_int_v *s)
{
	if (f->x < s->x)
		sign->x = 1;
	else
		sign->x = -1;
}

void	check_sign_y(t_int_v *f, t_int_v *sign, t_int_v *s)
{
	if (f->y < s->y)
		sign->y = 1;
	else
		sign->y = -1;
}

int	draw_walls_color(int i, t_map_editor *ed)
{
	if (i == ed->map.selected_circuit)
		return (0xFF0000);
	else
		return (0xFFFF00);
}
