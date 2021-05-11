/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_o.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:50:54 by aagrivan          #+#    #+#             */
/*   Updated: 2021/05/12 00:37:30 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	precision_less_width_if(t_printf *f, int length, int res)
{
	if (f->precis <= length)
	{
		if (f->fh && res != 0)
			ft_ispacing(' ', f, (length + 1));
		else
			ft_ispacing(' ', f, length);
		if (f->fh && res != 0)
		{
			ft_putchar('0');
			f->len++;
		}
		else if (!f->fh && res == 0)
			ft_ispacing(' ', f, length + 3);
	}
}

static void	precision_less_width(t_printf *f, int length, int res)
{
	if (f->precis <= length)
	{
		precision_less_width_if(f, length, res);
	}
	else if (f->precis < f->width)
	{
		if (f->fh && res != 0)
			ft_ispacing(' ', f, f->precis + 1);
		else
			ft_ispacing(' ', f, f->precis);
		if (f->fh && res != 0)
		{
			ft_putchar('0');
			f->len++;
		}
		ft_ispacing('0', f, (f->width - f->precis + length));
	}
}

static void	o_print_fl_with_fm(t_printf *f, int length, int res)
{
	if (f->fz)
	{
		if (f->fh && res != 0)
		{
			ft_putchar('0');
			f->len++;
		}
		if (f->fh && res != 0)
			ft_ispacing('0', f, (length + 1));
		else
			ft_ispacing('0', f, length);
	}
	else if (!f->fz && (f->precis >= f->width))
	{
		if (f->fh && res != 0 && f->precis <= 0)
		{
			ft_putchar('0');
			f->len++;
		}
		ft_ispacing('0', f, (length + 1));
	}
	else
		precision_less_width(f, length, res);
}

static void	o_pr_fl_without_fm(t_printf *f, int length, int res)
{
	if (f->precis >= f->width)
	{
		if (f->fh && res != 0)
		{
			ft_putchar('0');
			f->len++;
		}
		if (f->fh && res != 0)
			ft_ispacing('0', f, length);
		else
			ft_ispacing('0', f, length + 1);
	}
	else
	{
		if (f->fh && res != 0)
		{
			ft_putchar('0');
			f->len++;
		}
		if (!(f->precis <= length))
			ft_ispacing('0', f, (f->width - f->precis + length));
	}
}

void	ft_print_oint(t_printf *f)
{
	uintmax_t			res;
	unsigned int		length;
	char				*s;

	res = ft_get_unum_modlen(f);
	s = ftbaseull(res, 8, 'a');
	length = ft_strlen(s);
	if (f->width >= 0 && !f->fm)
		o_print_fl_with_fm(f, length, res);
	else if (f->width >= 0 && f->fm)
		o_pr_fl_without_fm(f, length, res);
	if (!(f->precis == 0 && res == 0 && !f->fh))
		ft_putstr(s);
	ft_print_oint_if(f, length, res);
	if (!(f->precis == 0 && res == 0 && !f->fh))
		f->len += length;
	free(s);
}
