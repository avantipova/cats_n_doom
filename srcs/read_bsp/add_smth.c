/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_smth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:27:45 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 16:27:18 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static char	*check_smth_2(char *ptr, t_bsp *node, char *key)
{
	if (!ft_strcmp(key, "uv_ids"))
	{
		ptr = ft_strchr(ptr, '[') + 1;
		node->vt_trs[node->vt_trs_count].uv_ids[0] = ft_atoi(ptr);
		ptr = ft_strchr(ptr, ',') + 1;
		node->vt_trs[node->vt_trs_count].uv_ids[1] = ft_atoi(ptr);
		ptr = ft_strchr(ptr, ',') + 1;
		node->vt_trs[node->vt_trs_count].uv_ids[2] = ft_atoi(ptr);
		ptr = ft_strchr(ptr, ']') + 1;
	}
	else if (!ft_strcmp(key, "type"))
	{
		node->vt_trs[node->vt_trs_count].type = ft_atoi(ptr);
		while (*ptr == ' ' || *ptr == '\t' || \
				*ptr == '\n' || *ptr == ',' || ft_isdigit(*ptr))
			ptr++;
	}
	return (ptr);
}

static char	*check_smth(char *ptr, t_bsp *node, char *key)
{
	if (!ft_strcmp(key, "ids"))
	{
		ptr = ft_strchr(ptr, '[') + 1;
		node->vt_trs[node->vt_trs_count].ids[0] = ft_atoi(ptr);
		ptr = ft_strchr(ptr, ',') + 1;
		node->vt_trs[node->vt_trs_count].ids[1] = ft_atoi(ptr);
		ptr = ft_strchr(ptr, ',') + 1;
		node->vt_trs[node->vt_trs_count].ids[2] = ft_atoi(ptr);
		ptr = ft_strchr(ptr, ']') + 1;
	}
	else if (!ft_strcmp(key, "n_ids"))
	{
		ptr = ft_strchr(ptr, '[') + 1;
		node->vt_trs[node->vt_trs_count].n_ids[0] = ft_atoi(ptr);
		ptr = ft_strchr(ptr, ',') + 1;
		node->vt_trs[node->vt_trs_count].n_ids[1] = ft_atoi(ptr);
		ptr = ft_strchr(ptr, ',') + 1;
		node->vt_trs[node->vt_trs_count].n_ids[2] = ft_atoi(ptr);
		ptr = ft_strchr(ptr, ']') + 1;
	}
	else
		return (check_smth_2(ptr, node, key));
	return (ptr);
}

char	*add_vt_tr(t_bsp *node, char *str)
{
	char	key[32];
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || \
				*ptr == '\n' || *ptr == '{' || *ptr == ',')
			ptr++;
		if (*ptr == '"')
		{
			ptr++;
			ft_strncpy(key, ptr, ft_strchr(ptr, '"') - ptr);
			key[ft_strchr(ptr, '"') - ptr] = 0;
			ptr = ft_strchr(ptr, ':') + 1;
			ptr = check_smth(ptr, node, key);
		}
		else if (*ptr == '}')
			break ;
	}
	(node->vt_trs_count)++;
	return (ft_strchr(ptr, '}') + 1);
}
