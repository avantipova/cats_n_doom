/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_di_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 21:43:24 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/11 23:01:27 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pr_fl_with_wi_next(t_printf *f, long long res, int length)
{
	if (res < 0 || f->fp)
	{
		ft_ispacing(' ', f, length + 1);
		if (res >= 0 && f->fp)
			ft_putchar('+');
		else
			ft_putchar('-');
		f->len++;
	}
	else
	{
		if (res == 0 && f->precis == 0)
			ft_ispacing(' ', f, 0);
		else
			ft_ispacing(' ', f, length);
	}
}

void	t_print_int_if_res(intmax_t res, char *s)
{
	unsigned long long	res_c;

	if (res < -9223372036854775807)
	{
		res_c = (unsigned long long)LLONG_MAX + 1;
		s = ftbaseull(res_c, 10, 'a');
	}
	else
		s = ft_itoa_base_ll_pos(res, 10);
}

void	ft_print_address_if(t_printf *f, int length)
{
	if (f->width >= 0 && !f->fm)
	{
		if (f->precis > f->width)
		{
			ft_putstr("0x");
			ft_ispacing('0', f, length + 1);
		}
		else
		{
			ft_spacing(' ', f, length + 2);
			ft_putstr("0x");
		}
	}
}

void	ft_print_oint_if(t_printf *f, unsigned int length, uintmax_t res)
{
	if (f->width > 0 && f->fm)
	{
		if (f->precis <= length)
		{
			if (f->fh && res != 0)
				ft_ispacing(' ', f, (length + 1));
			else
				ft_ispacing(' ', f, length);
		}
		else if (f->precis < f->width)
		{
			if (f->fh && res != 0)
				ft_ispacing(' ', f, f->precis + 1);
			else
				ft_ispacing(' ', f, f->precis);
		}
	}
}
