/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utills.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:11:29 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/20 22:37:05 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
void	exitstatus()
{
	int	h;

	while (waitpid(-1, &h, 0) != -1)
	{
		if (WEXITSTATUS(h) == 0)
			s = 0;
		if (WEXITSTATUS(h) == 127)
			s = 127;
		if (WEXITSTATUS(h) == 1)
			s = 127;
	}
}

void	error(char *s)
{
	int	i;
	if(!s)
		return;
	i = 0;
	write(2, "afadlane$: ", 11);
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	write(2, ": command not found", 19);
	write(2, "\n", 1);
	exit(127);
}

char	*get_cmd(char **ptr,char*lst,t_env *p)
{
	int		l;
	int		i;
	char	*buff;
	i = 0;
	l = 0;
	buff = "";

	if (access(lst, F_OK) == 0)
		return (lst);
	if(check_env(p) == NULL)
	{
		write(2, lst, ft_strlen(lst));
		write(2, ": No such file or directory\n", 28);
		exit(127);
	}
	while (ptr[i])
	{
		buff = ft_strjoin(ptr[i], "/");
		buff = ft_strjoin(buff, lst);
		if (access(buff, F_OK) == 0)
			return (buff);
		free(buff);
		i++;
	}
	return (NULL);
}


char 	*check_env(t_env *p)
{
	while (p->next)
	{
		if (ft_strcmp(p->next->key, "PATH")==0)
			return (p->next->data);
		p = p->next;
	}
	return (NULL);
}

void	first_proccess(t_env *lst,char **ptr,char **env,char **cmd,t_minishell *p)
{
	
	int pid = fork();
	p->pid = pid;
	if (pid == 0)
	{
		if(__built__in__(lst,p,0) == 0)
			exit(0);
		else
		{
			if (p->out_id > 0)
				dup2(p->out_id, 1);
			else
				dup2(lst->fd[1], 1);
			dup2(p->in_id, 0);
			close(lst->fd[0]);
			if (get_cmd(ptr,cmd[0],lst) == NULL)
				error(cmd[0]);
			execve(get_cmd(ptr,cmd[0],lst),cmd, env);
		}
	}
}

void	last_proccess(t_env *lst,char **ptr,char **cmd,t_minishell *p)
{
	int pid1 = fork();
	p->pid = pid1;
	if (pid1 == 0)
	{  
		if (p->out_id > 0)
			if(__built__in__(lst,p,2) == 0)
				exit(0);
		if (__built__in__(lst, p, -1) == 0)
			exit(0);
		else
		{
			dup2(p->out_id, 1);
			dup2(lst->flag_fd, 0);
			close(lst->fd[1]);
			if (get_cmd(ptr,cmd[0],lst) == NULL)
				error(cmd[0]);
			execve(get_cmd(ptr, cmd[0],lst),cmd, get_env(lst));
		}
	}
}

void	midlle_proccess(t_env *lst,char **ptr,char **cmd,t_minishell *p)
{
	
	int pid1 = fork();
	p->pid = pid1;
	if (pid1 == 0)
	{
		if(__built__in__(lst,p,0) == 0)
			exit(0);
		else
		{	
			if (p->out_id > 0)
				dup2(p->out_id, 1);
			else
				dup2(lst->fd[1], 1);
			dup2(lst->flag_fd, 0);
			close(lst->fd[0]);
			
			if (get_cmd(ptr,cmd[0],lst) == NULL)
				error(cmd[0]);
			execve(get_cmd(ptr ,cmd[0],lst),cmd, get_env(lst));
		}
		exit(0);
	}
}

void	one_command(char **ptr,char **cmd,t_minishell *p,t_env *lst)
{	
	//printf("hhhhhh----\n");
	if (p->out_id > 0)
		if(__built__in__(lst,p,2) == 0)
			return;
	if (__built__in__(lst, p, 1) == 0)
		return;
	int pid = fork();
	p->pid = pid;
	if (pid == 0)
	{

		if (p->out_id > 0)
			dup2(p->out_id, 1);
		//else~
		//dup2(lst->fd[0], 0);
		dup2(p->in_id, 0);
		if (get_cmd(ptr,cmd[0],lst) == NULL)
			error(cmd[0]);
		execve(get_cmd(ptr,cmd[0],lst),cmd, get_env(lst));
	}
}
void    pipex(t_minishell *lst,t_env *p,char **env)
{

	char **ptr = ft_split(check_env(p), ':');

	if (lstsize(lst) == 1)
		one_command(ptr, lst->all_cmds, lst,p);
	else
	{
		pipe(p->fd);
		first_proccess(p, ptr, env,lst->all_cmds,lst);
		p->flag_fd = p->fd[0];
		close(p->fd[1]);
		lst = lst->next;
		while (2 <= lstsize(lst))
		{
			if (lst->pipe == 1)
			{
				pipe(p->fd);
				midlle_proccess(p, ptr,lst->all_cmds,lst);
				close(p->fd[1]);
				close(p->flag_fd);
				p->flag_fd = p->fd[0];
			}
			lst = lst->next;
		}
		last_proccess(p, ptr, lst->all_cmds,lst);
		close(p->flag_fd);
	}
	exitstatus();
									// " This is the way "
}