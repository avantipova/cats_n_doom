/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_scp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:05:29 by aagrivan          #+#    #+#             */
/*   Updated: 2021/05/11 22:47:14 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_all(t_printf *f)
{
	if (f->star == 1)
		ft_putstr("It's bonus\n");
	else
	{
		if (f->convs == 's')
			ft_print_str(f);
		if (f->convs == 'c')
			ft_print_char(f);
		if (f->convs == 'p')
			ft_print_address(f);
		if (f->convs == 'd' || f->convs == 'i')
			ft_print_int(f);
		if (f->convs == 'u' || f->convs == 'U')
			ft_print_uint(f);
		if (f->convs == 'o')
			ft_print_oint(f);
		if (f->convs == 'x' || f->convs == 'X')
			ft_print_xint(f);
		if (f->convs == 'f')
			init_f(f);
		if (f->convs == '%')
			ft_print_percent(f);
		if (f->convs == 'Z')
			ft_print_other(f);
	}
}

void	ft_print_str(t_printf *f)
{
	char			*res;
	int				length;

	res = va_arg(f->avs, char *);
	if (!res)
		res = "(null)";
	if (f->precis >= 0)
		res = ft_strndup(res, f->precis);
	length = ft_strlen(res);
	if (f->width > 0 && !f->fm)
	{
		if (f->fz)
			ft_spacing('0', f, length);
		else
			ft_spacing(' ', f, length);
	}
	ft_putstr(res);
	if (f->width > 0 && f->fm)
		ft_spacing(' ', f, length);
	f->len += length;
	if (f->precis >= 0)
		ft_strdel(&res);
}

void	ft_print_char(t_printf *f)
{
	int				res;
	int				length;

	if (ft_strcmp(f->modln, "l") == 0)
		res = (unsigned long)va_arg(f->avs, long int);
	else
		res = (char)va_arg(f->avs, int);
	length = 1;
	if (f->width > 0 && !f->fm)
	{
		if (f->fz)
			ft_spacing('0', f, length);
		else
			ft_spacing(' ', f, length);
	}
	ft_putchar(res);
	if (f->width > 0 && f->fm)
		ft_spacing(' ', f, length);
	f->len += length;
}

void	ft_print_address(t_printf *f)
{
	unsigned long	res;
	int				length;
	char			*s;

	res = (unsigned long)va_arg(f->avs, void *);
	s = ftbaseull(res, 16, 'a');
	length = ft_strlen(s);
	ft_print_address_if(f, length);
	if (f->fm)
		ft_putstr("0x");
	if (!(res == 0 && f->precis == 0))
		ft_putstr(s);
	if (f->width > 0 && f->fm)
		ft_spacing(' ', f, length + 2);
	if (res == 0 && f->precis == 0)
		(f->len += 2);
	else
		(f->len += length + 2);
	free(s);
}

void	ft_spacing(char c, t_printf *f, int length)
{
	int				lensp;

	lensp = f->width - length;
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
