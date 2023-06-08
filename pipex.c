/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:01:03 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/08 15:13:58 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	trim_pipex(t_minishell *lst, t_env *p)
{
	int	pid;

	pipe(p->fd);
	first_proccess(p, lst->all_cmds, lst);
	p->flag_fd = p->fd[0];
	close(p->fd[1]);
	lst = lst->next;
	while (2 <= lstsize(lst))
	{
		if (lst->pipe == 1)
		{
			pipe(p->fd);
			midlle_proccess(p, lst->all_cmds, lst);
			close(p->fd[1]);
			close(p->flag_fd);
			p->flag_fd = p->fd[0];
		}
		lst = lst->next;
	}
	pid = last_proccess(p, lst->all_cmds, lst);
	close(p->flag_fd);
	return (pid);
}

void	pipex(t_minishell *lst, t_env *p, t_object *obj)
{
	g_sig->flag = 0;
	g_sig->sst = 0;
	if (p->n >= 1)
	{
		main_herdoc(p, obj);
		if (!lst->all_cmds[0])
			return ;
	}
	if (!lst->all_cmds[0])
		return ;
	if (lstsize(lst) == 1)
		one_command(lst->all_cmds, lst, p);
	else
		exitstatus(trim_pipex(lst, p));
}
