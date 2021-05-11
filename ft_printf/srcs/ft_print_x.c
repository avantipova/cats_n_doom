/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:11:26 by aagrivan          #+#    #+#             */
/*   Updated: 2021/05/11 23:33:41 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	case_zero(t_printf *f, int res)
{
	if (f->fh && res != 0)
	{
		ft_putchar('0');
		ft_putchar(f->convs);
		f->len += 2;
	}
	return (f->len);
}

static void	x_print_fl_with_fm(t_printf *f, int length, int res)
{
	if (f->fz && f->precis < 0)
	{
		case_zero(f, res);
		if (f->fh && res != 0)
			ft_ispacing('0', f, length + 2);
		else
			ft_ispacing('0', f, length);
	}
	else if (f->precis >= f->width)
	{
		case_zero(f, res);
		ft_ispacing('0', f, (length + 1));
	}
	else if (f->precis <= length)
	{
		x_print_fl_with_fm_if_len(f, length, res);
	}
	else if (f->precis < f->width)
	{
		x_print_fl_with_fm_if_width(f, length, res);
	}
}

static void	x_pr_fl_with_fm(t_printf *f, int length, int res)
{
	if (f->precis >= f->width)
	{
		case_zero(f, res);
		ft_ispacing('0', f, length + 1);
	}
	else if (f->precis <= length)
	{
		case_zero(f, res);
	}
	else if (f->precis < f->width)
	{
		case_zero(f, res);
		ft_ispacing('0', f, (f->width - f->precis + length));
	}
}

static void	width_fm(t_printf *f, int length, int res)
{
	if (f->precis <= length)
	{
		if (res == 0 && f->precis == 0)
			ft_ispacing(' ', f, 0);
		else
		{
			if (f->fh && res != 0)
				ft_ispacing(' ', f, (length + 2));
			else
				ft_ispacing(' ', f, length);
		}
	}
	else if (f->precis < f->width)
	{
		if (f->fh && res != 0)
			ft_ispacing(' ', f, f->precis + 2);
		else
			ft_ispacing(' ', f, f->precis);
	}
}

void	ft_print_xint(t_printf *f)
{
	uintmax_t			res;
	unsigned int		length;
	char				*s;

	res = ft_get_unum_modlen(f);
	if (f->convs == 'x')
		s = ftbaseull(res, 16, 'a');
	else
		s = ftbaseull(res, 16, 'A');
	length = ft_strlen(s);
	if (f->width >= 0 && !f->fm)
		x_print_fl_with_fm(f, length, res);
	if (f->width >= 0 && f->fm)
		x_pr_fl_with_fm(f, length, res);
	if (!(f->precis == 0 && res == 0))
		ft_putstr(s);
	if (f->width > 0 && f->fm)
		width_fm(f, length, res);
	if (f->precis == 0 && res == 0)
		f->len += length;
	free(s);
}
