/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:43:46 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 21:11:58 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static unsigned int	*intrandom(void)
{
	char			str[160];
	int				fd;
	unsigned int	*intrand;

	fd = open("/dev/urandom", O_RDONLY);
	read(fd, str, 160);
	close(fd);
	intrand = (unsigned int *)str;
	return (intrand);
}

static void	length_check(t_doom *doom, t_vertex	*new_pos, \
									unsigned int *intrand, int i)
{
	if (length(sub(doom->scene.camera.position, \
			doom->enemies[i].sprite.instance.position)) < 2.0)
	{
		doom->enemies[i].in_attak = 1;
		doom->enemies[i].attak_anim.curr_f = 0.0;
		doom->health -= doom->enemy_damage;
		if (doom->health <= 0)
			doom->lose = 1;
	}
	else if (length(sub(doom->scene.camera.position, \
		doom->enemies[i].sprite.instance.position)) < 15.0)
	{
		*new_pos = sub(doom->scene.camera.position,
				doom->enemies[i].sprite.instance.position);
		doom->enemies[i].beta = atan2(new_pos->x, -new_pos->z) / M_PI * 180;
	}
	else if (intrand[i] < 96256808)
		doom->enemies[i].beta += intrand[i] % 180;
}

static void	update_enemies_2(t_doom *doom, t_vertex	*new_pos, int i)
{
	float	floor_ceil[2];
	float	speed;

	speed = doom->enemy_speed;
	get_floor_seil_traversal(&doom->scene.level.root, \
			(t_vertex){doom->enemies[i].sprite.instance.position.x, \
			doom->enemies[i].sprite.instance.position.z, \
			0.0}, &floor_ceil[0], &floor_ceil[1]);
	doom->enemies[i].on_ground = 0;
	doom->enemies[i].g_speed += 0.4 * (doom->mgl->curr_time \
												- doom->mgl->lst_time);
	doom->enemies[i].sprite.instance.position.y -= doom->enemies[i].g_speed;
	if (doom->enemies[i].sprite.instance.position.y - 1.0 < floor_ceil[0])
	{
		doom->enemies[i].on_ground = 1;
		doom->enemies[i].sprite.instance.position.y = 1.0 + floor_ceil[0];
		doom->enemies[i].g_speed = 0;
	}
	new_pos->x = doom->enemies[i].sprite.instance.position.x + \
			speed * sin(doom->enemies[i].beta / 180 * M_PI);
	new_pos->y = doom->enemies[i].sprite.instance.position.z - \
			speed * cos(doom->enemies[i].beta / 180 * M_PI);
	new_pos->z = doom->enemies[i].sprite.instance.position.y;
}

void	update_enemies(t_doom *doom)
{
	int				i;
	unsigned int	*intrand;
	t_vertex		new_pos;

	intrand = intrandom();
	i = -1;
	while (++i < doom->enemies_count)
	{
		if (doom->enemies[i].health <= 0 || \
					doom->enemies[i].damaged || doom->enemies[i].in_attak)
		{
			i++;
			continue ;
		}
		length_check(doom, &new_pos, intrand, i);
		update_enemies_2(doom, &new_pos, i);
		if (if_possible_to_move(new_pos, &doom->scene.level.root,
				PHISICS_MODE_PLAYER, 1))
		{
			doom->enemies[i].sprite.instance.position.x = new_pos.x;
			doom->enemies[i].sprite.instance.position.z = new_pos.y;
		}
	}
}
