/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_di.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 19:26:59 by aagrivan          #+#    #+#             */
/*   Updated: 2021/05/11 21:55:43 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	prec_big_width(t_printf *f, long long res, int length)
{
	if (res < 0 || f->fp)
		ft_ispacing(' ', f, f->precis + 1);
	else
		ft_ispacing(' ', f, f->precis);
	if (res < 0 || f->fp)
	{
		if (res >= 0 && f->fp)
			ft_putchar('+');
		else
			ft_putchar('-');
		f->len++;
	}
	ft_ispacing('0', f, (f->width - f->precis + length));
}

static void	pr_fl_with_wi(t_printf *f, long long res, int length)
{
	if (f->fz && f->precis < 0)
	{
		print_sign(f, res, length);
		ft_ispacing('0', f, (length + 1));
	}
	else if (f->precis >= f->width)
	{
		print_sign(f, res, length);
		ft_ispacing('0', f, (length + 1));
	}
	else if (f->precis <= length)
	{
		pr_fl_with_wi_next(f, res, length);
	}
	else if (f->precis < f->width)
		prec_big_width(f, res, length);
}

static void	pr_fl_out_wi(t_printf *f, long long res, int length)
{
	if (res < 0)
	{
		ft_putchar('-');
		f->len++;
	}
	if (res >= 0 && (f->fp || f->fs))
	{
		if (f->fp && res >= 0)
			ft_putchar('+');
		if (f->fs && !f->fp && res > 0)
			ft_putchar(' ');
		f->len++;
	}
	if (f->precis >= f->width)
		ft_ispacing('0', f, (length + 1));
	else
		if (!(f->fz && f->fp && f->fs && f->fm && f->precis > 0))
			ft_ispacing('0', f, (((f->width - f->precis) + length)));
}

static void	width_fm_print(t_printf *f, long long res, int length)
{
	if (f->precis < f->width)
	{
		if (f->precis > length)
		{
			if (f->fz && f->fp && f->fs && f->fm && f->precis > 0)
				ft_ispacing(' ', f, length + 1);
			else if (f->fp || f->fs || res < 0)
				ft_ispacing(' ', f, f->precis + 1);
			else
				ft_ispacing(' ', f, f->precis);
		}
		else
		{
			if (f->fp || f->fs || res < 0)
				ft_ispacing(' ', f, length + 1);
			else if (res == 0 && f->precis >= 0)
				ft_ispacing(' ', f, 0);
			else
				ft_ispacing(' ', f, length);
		}
	}
}

void	t_print_int(t_printf *f)
{
	intmax_t			res;
	int					length;
	char				*s;
	char				zero;

	zero = '0';
	s = 0;
	res = ft_get_num_modlen(f);
	if (!res)
		zero = '1';
	t_print_int_if_res(res, s);
	length = ft_strlen(s);
	if (f->width > 0 && !f->fm)
		pr_fl_with_wi(f, res, length);
	else if (f->width == 0 || (f->width > 0 && f->fm))
		pr_fl_out_wi(f, res, length);
	if (!(f->precis == 0 && zero == '1'))
		ft_putstr(s);
	if (f->width > 0 && f->fm)
		width_fm_print(f, res, length);
	if (f->precis == 0 && zero == '1')
		(f->len += 0);
	else
		(f->len += length);
	free(s);
}
