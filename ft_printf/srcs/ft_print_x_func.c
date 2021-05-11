/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 23:28:47 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/12 00:22:37 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	x_print_fl_with_fm_if_len(t_printf *f, int length, int res)
{
	if (f->fh && res != 0)
		ft_ispacing(' ', f, (length + 2));
	else
		ft_ispacing(' ', f, length);
	case_zero(f, res);
	if (!f->fh && res == 0)
		ft_ispacing(' ', f, length + 3);
}

void	x_print_fl_with_fm_if_width(t_printf *f, int length, int res)
{
	if (f->fh && res != 0)
		ft_ispacing(' ', f, f->precis + 2);
	else
		ft_ispacing(' ', f, f->precis);
	case_zero(f, res);
	ft_ispacing('0', f, (f->width - f->precis + length));
}

void	ft_ispacing_else(char c, t_printf *f, int length)
{
	int		lensp;

	lensp = f->precis - (length - 1);
	if (lensp > 0)
	{
		while (lensp > 0)
		{
			ft_putchar(c);
			f->len++;
			lensp--;
		}
	}
}
