/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 10:08:26 by poatmeal          #+#    #+#             */
/*   Updated: 2021/05/12 00:36:03 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	free_buf(t_buf *buf)
{
	free(buf->div_num);
	free(buf->wh_num);
	free(buf->pow_2);
	free(buf->pow_5);
}

int	mem_alloc_2(t_buf *buf)
{
	buf->pow_2 = (char *)ft_memalloc(sizeof(char) * BIG_BUFF + 1);
	if (buf->pow_2 == NULL)
	{
		free(buf->wh_num);
		free(buf->div_num);
		return (0);
	}
	ft_memset(buf->pow_2, -1, BIG_BUFF);
	buf->pow_5 = (char *)ft_memalloc(sizeof(char) * BIG_BUFF + 1);
	if (buf->pow_5 == NULL)
	{
		free(buf->wh_num);
		free(buf->div_num);
		free(buf->pow_5);
		return (0);
	}
	ft_memset(buf->pow_5, -1, BIG_BUFF);
	return (1);
}

int	mem_alloc(t_buf *buf)
{
	buf->wh_num = (char *)ft_memalloc(sizeof(char) * BIG_BUFF + 1);
	if (buf->wh_num == NULL)
		return (0);
	ft_memset(buf->wh_num, -1, BIG_BUFF);
	buf->div_num = (char *)ft_memalloc(sizeof(char) * BIG_BUFF + 1);
	if (buf->div_num == NULL)
	{
		free(buf->wh_num);
		return (0);
	}
	ft_memset(buf->div_num, -1, BIG_BUFF);
	return (mem_alloc_2(buf));
}
