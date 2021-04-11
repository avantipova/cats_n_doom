/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:32:21 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 18:39:19 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static int	strlen_while_dig(char *str)
{
	int	len;

	len = 0;
	while (str)
	{
		if (!isdigit(*str))
			break ;
		str++;
		len++;
	}
	return (len);
}

float	ft_atof(char *str)
{
	float	ret;
	float	mod;
	int		neg;

	while ((*str == '\n') || (*str == '\t') || (*str == '\v') || \
			(*str == ' ') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-')
		neg = 1;
	else
		neg = 0;
	ret = (float)atoi(str);
	if (!strchr(str, '.'))
		return (ret);
	str = strchr(str, '.') + 1;
	if (isdigit(*str))
	{
		mod = (float)atoi(str);
		mod /= pow(10, strlen_while_dig(str));
		if (neg)
			ret += -mod;
		else
			ret += mod;
	}
	return (ret);
}
