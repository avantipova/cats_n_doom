/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 18:19:23 by aagrivan          #+#    #+#             */
/*   Updated: 2021/05/11 22:05:14 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_percent(t_printf *f)
{
	int				length;

	length = 1;
	if (f->width > 0 && !f->fm)
	{
		if (f->fz)
			ft_spacing('0', f, 1);
		else
			ft_spacing(' ', f, 1);
	}
	ft_putchar('%');
	if (f->width > 0 && f->fm)
		ft_spacing(' ', f, 1);
	f->len += length;
}

void	ft_print_other(t_printf *f)
{
	int				length;

	length = 0;
	if (f->convs == 'Z')
	{
		ft_putchar('Z');
		f->len++;
	}
	f->len += length;
}
