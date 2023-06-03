/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:04:31 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/30 17:09:25 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__check_add(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

int	check_flag(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	norm_export(t_env *lst)
{
	g_sig->ft_flag = 1;
	if (__check_add(lst->ptr[0]) == 0)
		g_sig->ft_flag = 0;
	__check_data_exit(lst, lst->ptr, g_sig->ft_flag);
	lst->p = ft_split(lst->ptr[0], '+');
}