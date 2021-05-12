/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:54:45 by mjoss             #+#    #+#             */
/*   Updated: 2021/05/12 22:59:50 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"
#include "archiver.h"

void	check_arguments(int	ac, char **av)
{
	if (ac < 2)
	{
		ft_putendl("usage: ./DoomNukem [your_map]");
		exit(-2);
	}
	dearchivate(av[1]);
	if (!check_hash(ASSETS_FOLDER_NAME "/"))
	{
		ft_putendl("Файлы повреждены");
		exit(-2);
	}
}
