/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 14:28:26 by poatmeal          #+#    #+#             */
/*   Updated: 2021/05/12 00:35:05 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	change_whole(t_buf *buf)
{
	int		j;

	j = 0;
	if (buf->wh_num[BIG_BUFF] + 1 > 9)
	{
		while (buf->wh_num[BIG_BUFF - j] + 1 > 9)
		{
			buf->wh_num[BIG_BUFF - j] = 0;
			j++;
		}
	}
	if (buf->wh_num[BIG_BUFF - j] == -1)
		buf->wh_num[BIG_BUFF - j] = 1;
	else
		buf->wh_num[BIG_BUFF - j] = buf->wh_num[BIG_BUFF - j] + 1;
}

void	change_div(t_buf *buf, int i)
{
	if (buf->div_num[i] + 1 > 9)
	{
		while (i >= 0 && buf->div_num[i] + 1 > 9)
		{
			buf->div_num[i] = 0;
			i--;
		}
	}
	if (i < 0)
		change_whole(buf);
	else
		buf->div_num[i] = buf->div_num[i] + 1;
}
