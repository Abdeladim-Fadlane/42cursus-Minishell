/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:11:29 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/08 15:11:26 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_midlle(t_env *lst, char **cmd, t_minishell *p, char **ptr)
{
	char	*s;

	if (p->out_id > 0)
	{
		dup2(p->out_id, 1);
		g_sig->flag = 1;
	}
	else
		dup2(lst->fd[1], 1);
	dup2(lst->flag_fd, 0);
	close(lst->fd[0]);
	s = get_cmd(ptr, cmd[0], lst);
	if (s == NULL)
		error(cmd[0]);
	execve(s, cmd, get_env(lst));
}

void	midlle_proccess(t_env *lst, char **cmd, t_minishell *p)
{
	int		pid1;
	char	**ptr;

	g_sig->signal = 1;
	pid1 = fork();
	if (pid1 == 0)
	{
		ptr = ft_split(check_env(lst), ':');
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
			norm_midlle(lst, cmd, p, ptr);
	}
}

int	norm_one_cmd(t_env *lst, t_minishell *p)
{
	if (p->out_id > 0)
	{
		if (__built__in__(lst, p, 2) == 0)
		{
			g_sig->status = 0;
			if (g_sig->sst == 1)
				g_sig->status = 1;
			if (g_sig->sst == 127)
				g_sig->status = 127;
			return (0);
		}
	}
	if (__built__in__(lst, p, 1) == 0)
	{
		g_sig->status = 0;
		if (g_sig->sst == 1)
			g_sig->status = 1;
		if (g_sig->sst == 127)
			g_sig->status = 127;
		return (0);
	}
	return (1);
}

void	one_cmd(char **cmd, t_env *lst)
{
	char	*s;
	char	**ptr;

	ptr = ft_split(check_env(lst), ':');
	s = get_cmd(ptr, cmd[0], lst);
	if (s == NULL)
		error(cmd[0]);
	execve(s, cmd, get_env(lst));
}

void	one_command(char **cmd, t_minishell *p, t_env *lst)
{
	int	pid;

	g_sig->signal = 1;
	if (norm_one_cmd(lst, p) == 0)
		return ;
	else
		g_sig->status = 1;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (p->out_id > 0)
			dup2(p->out_id, 1);
		if (p->in_id > 0)
			dup2(p->in_id, 0);
		else
			dup2(lst->fd2[0], 0);
		one_cmd(cmd, lst);
	}
	exitstatus(pid);
}
