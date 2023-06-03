/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utills.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:11:29 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/03 14:40:33 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_proccess(t_env *lst, char **cmd, t_minishell *p)
{
	int		pid;
	char	**ptr;
	char	*s;

	g_sig->signal = 1;
	pid = fork();
	if (pid == 0)
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
		{
			if (p->out_id > 0)
				dup2(p->out_id, 1);
			else
				dup2(lst->fd[1], 1);
			// if (lst->fd2[0] > 0)
			// 	dup2(lst->fd2[0], 0);
			// else
			dup2(p->in_id, 0);
			close(lst->fd[0]);
			s = get_cmd(ptr, cmd[0], lst);
			if (s == NULL)
				error(cmd[0]);
			execve(s, cmd, get_env(lst));
		}
	}
	//close(lst->fd2[0]);
}

int	last_proccess(t_env *lst, char **cmd, t_minishell *p)
{
	int		pid1;
	char	**ptr;
	char	*s;

	g_sig->signal = 1;
	pid1 = fork();
	if (pid1 == 0)
	{
		ptr = ft_split(check_env(lst), ':');
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (p->out_id > 0)
			if (__built__in__(lst, p, 2) == 0)
				exit(g_sig->sst);
		if (__built__in__(lst, p, -1) == 0)
			exit(g_sig->sst);
		else
		{
			if (p->all_cmds[0] == NULL)
				exit(0);
			dup2(p->out_id, 1);
			dup2(lst->flag_fd, 0);
			close(lst->fd[1]);
			s = get_cmd(ptr, cmd[0], lst);
			if (s == NULL)
				error(cmd[0]);
			execve(s, cmd, get_env(lst));
		}
	}
	return (pid1);
}

void	midlle_proccess(t_env *lst, char **cmd, t_minishell *p)
{
	int		pid1;
	char	**ptr;
	char	*s;

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
		{
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
		//exit(0);
	}
}

int	norm_one_cmd(t_env *lst, t_minishell *p)
{
	g_sig->signal = 1;
	if (p->out_id > 0)
		if (__built__in__(lst, p, 2) == 0)
		{
			g_sig->status = 0;
			if (g_sig->sst == 1)
				g_sig->status = 1;
			if (g_sig->sst == 127)
				g_sig->status = 127;
			return (0);
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

void	one_command(char **cmd, t_minishell *p, t_env *lst)
{
	int		pid;
	char	**ptr;
	char	*s;

	if (norm_one_cmd(lst, p) == 0)
		return ;
	else
		g_sig->status = 1;
	pid = fork();
	if (pid == 0)
	{
		ptr = ft_split(check_env(lst), ':');
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (p->out_id > 0)
			dup2(p->out_id, 1);
		if (p->in_id > 0)
			dup2(p->in_id, 0);
		else
			dup2(lst->fd2[0], 0);
		s = get_cmd(ptr, cmd[0], lst);
		if (s == NULL)
			error(cmd[0]);
		execve(s, cmd, get_env(lst));
	}
	exitstatus(pid);
}

void	main_herdoc(t_env *p, t_object *obj)
{
	while (obj)
	{
		her_doc(obj->s, p);
		obj = obj->next;
	}
}
