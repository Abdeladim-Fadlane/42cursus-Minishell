/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:59:52 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/09 11:16:17 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_first(t_env *lst, char **cmd, t_minishell *p)
{
	char	*s;
	char	**ptr;

	ptr = ft_split(check_env(lst), ':');
	if (p->out_id > 0)
		dup2(p->out_id, 1);
	else
		dup2(lst->fd[1], 1);
	dup2(p->in_id, 0);
	close(lst->fd[0]);
	s = get_cmd(ptr, cmd[0], lst);
	if (s == NULL)
		error(cmd[0]);
	execve(s, cmd, get_env(lst));
}

void	first_proccess(t_env *lst, char **cmd, t_minishell *p)
{
	int	pid;

	g_sig->signal = 1;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (__built__in__(lst, p, 0) == 0)
		{
			if (g_sig->sst == 1)
				exit(1);
			else
				exit(0);
		}
		else
			norm_first(lst, cmd, p);
	}
}

void	norm_last(t_env *lst, char **cmd, t_minishell *p)
{
	char	*s;
	char	**ptr;

	ptr = ft_split(check_env(lst), ':');
	if (p->all_cmds[0] == NULL)
		exit(0);
	dup2(p->out_id, 1);
	if(p->in_id > 0)
		dup2(p->in_id, 0);
	else
		dup2(lst->flag_fd, 0);
	close(lst->fd[1]);
	s = get_cmd(ptr, cmd[0], lst);
	if (s == NULL)
		error(cmd[0]);
	execve(s, cmd, get_env(lst));
}

int	last_proccess(t_env *lst, char **cmd, t_minishell *p)
{
	int	pid1;

	g_sig->signal = 1;
	pid1 = fork();
	if (pid1 == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (p->out_id > 0)
			if (__built__in__(lst, p, 2) == 0)
				exit(g_sig->sst);
		if (__built__in__(lst, p, -1) == 0)
			exit(g_sig->sst);
		else
			norm_last(lst, cmd, p);
	}
	return (pid1);
}
