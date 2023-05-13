/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utills.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:11:29 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/13 22:48:29 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
void	exitstatus(t_minishell *p)
{
	//int	y;
	int	h;
	(void)p;
	// y = 0;
	while (waitpid(-1, &h, 0) != -1)
		;
	// {
	// 	if (WEXITSTATUS(h) == 0)
	// 	{
	// 		while (p)
	// 		{
	// 			kill(p->pid, 9);
	// 			p = p->next;
	// 		}
	// 	}
	// }
}

void	error(char *s)
{
	int	i;

	i = 0;
	write(2, "command not found : ", 21);
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	//write(2, "\n", 1);
	exit(0);
}

char	*get_cmd(char **ptr,char*lst)
{
	int		l;
	int		i;
	char	*buff;
	i = 0;
	l = 0;
	buff = "";

	if (access(lst, F_OK) == 0)
		return (lst);
	while (ptr[i])
	{
		buff = ft_strjoin(ptr[i], "/");
		buff = ft_strjoin(buff, lst);
		if (access(buff, F_OK) == 0)
			return (buff);
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
		//printf("------%d\n", lst->fd[0]);
		dup2(p->in_id, 0);
		close(lst->fd[0]);
		dup2(lst->fd[1], 1);
		if (get_cmd(ptr,cmd[0]) == NULL)
			error("command not found\n");
		execve(get_cmd(ptr,cmd[0]),cmd, env);
		//printf("%s: command not found\n", lst->all_cmds[0]);
	}
}

void	last_proccess(t_env *lst,char **ptr,char **env,char **cmd,t_minishell *p)
{
	int pid1 = fork();
	p->pid = pid1;
	if (pid1 == 0)
	{   
		//printf("%d-----\n", lst->cmd->flag_fd);
		dup2(p->out_id, 1);
		dup2(lst->flag_fd, 0);
		close(lst->fd[1]);
		if (get_cmd(ptr,cmd[0]) == NULL)
			error("command not found\n");
		execve(get_cmd(ptr, cmd[0]),cmd, env);
		//printf("%s: command not found\n", lst->all_cmds[0]);
	}
}

void	midlle_proccess(t_env *lst,char **ptr,char **env,char **cmd,t_minishell *p)
{
	
	int pid1 = fork();
	p->pid = pid1;
	if (pid1 == 0)
	{     
		dup2(lst->flag_fd, 0);
		close(lst->fd[0]);
		dup2(lst->fd[1], 1);
		if (get_cmd(ptr,cmd[0]) == NULL)
			error("command not found\n");
		execve(get_cmd(ptr,cmd[0]),cmd, env);
		//printf("%s: command not found\n",cmds[0]);
	}
}

// void	second_proccess(t_env *lst,char **ptr,char **env,char **cmd,t_minishell *p)
// {
// 	int pid1 = fork();
// 	p->pid = pid1;
// 	if (pid1 == 0)
// 	{   
// 		//printf("%d-----\n", lst->cmd->flag_fd);
// 		dup2(p->out_id, 1);
// 		//dup2(lst->flag_fd, 0);
// 		close(lst->fd[1]);
// 		if (get_cmd(ptr,cmd[0]) == NULL)
// 			error("command not found\n");
// 		execve(get_cmd(ptr, cmd[0]),cmd, env);
// 		//printf("%s: command not found\n", lst->all_cmds[0]);
// 	}
// }
void	one_command(char **ptr,char **env,char **cmd,t_minishell *p)
{
	int pid = fork();
	p->pid = pid;
	if (pid == 0)
	{
		//printf("------%d\n", lst->fd[0]);
		dup2(p->in_id, 0);
		if (get_cmd(ptr,cmd[0]) == NULL)
			error("command not found\n");
		execve(get_cmd(ptr,cmd[0]),cmd, env);
		//printf("%s: command not found\n", lst->all_cmds[0]);
	}
}
void    pipex(t_minishell *lst,t_env *p,char **env)
{
	//t_minishell *lst1 = lst;
	if (check_env(p) == NULL)
		printf("path not found\n");
	char **ptr = ft_split(check_env(p), ':');
	if(lst->next == NULL)
		one_command(ptr, env, lst->all_cmds, lst);
	else
	{
		pipe(p->fd);
		first_proccess(p, ptr, env,lst->all_cmds,lst);
		p->flag_fd = p->fd[0];
		close(p->fd[1]);
		while (lst)
		{
			//printf("%s\n", lst->all_cmds[0]);
			if (lst->pipe == 1)
			{
				//printf("-----kkk----%s-----here\n",lst->all_cmds[0]);
				pipe(p->fd);
				midlle_proccess(p, ptr, env,lst->all_cmds,lst);
				close(p->fd[1]);
				close(p->flag_fd);
				p->flag_fd = p->fd[0];
			}
			if(lst->pipe == 0)
			{
				last_proccess(p, ptr, env, lst->all_cmds,lst);
				
				close(p->flag_fd);
			}
			lst = lst->next;
		}
	}

	//exitstatus(lst1);
	while (wait(NULL) != -1)
		;
	
}