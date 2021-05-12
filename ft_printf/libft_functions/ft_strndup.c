/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 19:09:55 by aagrivan          #+#    #+#             */
/*   Updated: 2021/05/12 22:16:16 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strndup(const char *str, int count)
{
	char	*cp;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	cp = (char *)malloc(sizeof(char) + count + 1);
	if (cp == NULL)
		return (NULL);
	while (i < count)
	{
		cp[i] = str[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
