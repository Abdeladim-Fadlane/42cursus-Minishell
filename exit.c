/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:35:41 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/08 12:50:43 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_minishell *list)
{
	if (ft_strcmp(list->all_cmds[0], "exit") == 0
		|| ft_strcmp(list->all_cmds[0], "EXIT") == 0)
	{
		printf("exit\n");
		if (list->all_cmds[1] == NULL)
			exit(0);
		if ((ft_atoi(list->all_cmds[1]) == 0 && list->all_cmds[1][0] != '0'))
		{
			write(2, "afadlane$: numeric argument required\n", 38);
			exit(255);
		}
		if (list->all_cmds[1] != NULL)
			exit(ft_atoi(list->all_cmds[1]));
	}
}
