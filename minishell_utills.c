/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utills.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:11:29 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/26 17:28:29 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_proccess(t_env *lst, char **ptr, char **cmd, t_minishell *p)
{
	int	pid;

	sig->signal = 1;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (__built__in__(lst, p, 0) == 0)
			exit(0);
		else
		{
			if (p->out_id > 0)
				dup2(p->out_id, 1);
			else
				dup2(lst->fd[1], 1);
			if (lst->fd2[0] > 0)
				dup2(lst->fd2[0], 0);
			else
				dup2(p->in_id, 0);
			close(lst->fd[0]);
			if (get_cmd(ptr, cmd[0], lst) == NULL)
				error(cmd[0]);
			execve(get_cmd(ptr, cmd[0], lst), cmd, get_env(lst));
		}
	}
	//close(lst->fd2[0]);
}

int	last_proccess(t_env *lst, char **ptr, char **cmd, t_minishell *p)
{
	int	pid1;

	sig->signal = 1;
	pid1 = fork();
	p->pid = pid1;
	if (pid1 == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (p->out_id > 0)
			if (__built__in__(lst, p, 2) == 0)
				exit(0);
		if (__built__in__(lst, p, -1) == 0)
			exit(0);
		else
		{
			dup2(p->out_id, 1);
			dup2(lst->flag_fd, 0);
			close(lst->fd[1]);
			if (get_cmd(ptr, cmd[0], lst) == NULL)
				error(cmd[0]);
			execve(get_cmd(ptr, cmd[0], lst), cmd, get_env(lst));
		}
	}
	return (pid1);
}

void	midlle_proccess(t_env *lst, char **ptr, char **cmd, t_minishell *p)
{
	int	pid1;
	sig->signal = 1;
	pid1 = fork();
	if (pid1 == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		
		if (__built__in__(lst, p, 0) == 0)
			exit(0);
		else
		{
			if (p->out_id > 0)
				dup2(p->out_id, 1);
			else
				dup2(lst->fd[1], 1);
			dup2(lst->flag_fd, 0);
			close(lst->fd[0]);
			if (get_cmd(ptr, cmd[0], lst) == NULL)
				error(cmd[0]);
			execve(get_cmd(ptr, cmd[0], lst), cmd, get_env(lst));
		}
		//exit(0);
	}
}

void	one_command(char **ptr, char **cmd, t_minishell *p, t_env *lst)
{
	int	pid;
	sig->signal = 1;
	if (p->out_id > 0)
		if (__built__in__(lst, p, 2) == 0)
		{
				sig->status = 0;
				return ;
		}	
	if (__built__in__(lst, p, 1) == 0)
	{
			sig->status = 0;
			return ;
	}
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
		char *s = get_cmd(ptr, cmd[0], lst);
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
