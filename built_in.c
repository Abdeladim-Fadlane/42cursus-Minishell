/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:23 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/20 22:15:48 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	__pwd__(int k,int fd,int fd_out)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		if(fd_out>0)
		{
			ft_putstr_fd(path, fd_out);
			write( fd_out, "\n", 1);
		}	
		else if(k == 0)
		{
			ft_putstr_fd(path, fd);
			write(fd, "\n", 1);
		}	
		else
		{
			ft_putstr_fd(path, 1);
			write(1, "\n", 1);
		}
	}
	else
		perror("getcwd() error");
}
void	put_str(char *s,int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i++;
		else
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	__echo__(t_minishell *lst,int k,int fd,int fdd)
{
	int		i;

	i = 1;
	if (lst->all_cmds[1] == NULL)
	{
		if(fdd>0)
			write(fdd, "\n", 1);
		if(k == 0)
			write(fd, "\n", 1);
		else 
			write(1, "\n", 1);
		return ;
	}
	if (ft_strcmp(lst->all_cmds[1],"$?") == 0)
	{
		printf("%d\n",s);
		return;
	}
	if (ft_strcmp(lst->all_cmds[1], "-n") == 0 && lst->all_cmds[1] == NULL)
		return ;
	else
	{
		while (ft_strcmp(lst->all_cmds[i], "-n") == 0)
			i++;
		while (lst->all_cmds[i])
		{
			if(fdd>0)
			{
				put_str(lst->all_cmds[i],fdd);
				if (lst->all_cmds[i + 1] != NULL)
					write(fdd, " ", 2);
			}
			else if(k == 0)
			{
				put_str(lst->all_cmds[i],fd);
				if (lst->all_cmds[i + 1] != NULL)
					write(fd, " ", 2);
			}
			else
			{
				put_str(lst->all_cmds[i],1);
				if (lst->all_cmds[i + 1] != NULL)
					write(1, " ", 2);
			}
			i++;
		}
	}
	if(fdd > 0)
	{
		if (ft_strcmp(lst->all_cmds[1], "-n") != 0)
			write(fdd, "\n", 1);
	}
	else if(k == 0)
	{
		if (ft_strcmp(lst->all_cmds[1], "-n") != 0)
			write(fd, "\n", 1);
	}
	else
	{

			if (ft_strcmp(lst->all_cmds[1], "-n") != 0)
				write(1, "\n",1);
	}
}
		

void	get_index_pwd(t_env *lst, char *path, char *s)
{
	int		i;
	t_env	*p;

	p = lst;
	i = 0;
	while (p)
	{
		if (ft_strcmp(p->key, "OLDPWD") == 0)
			p->data = ft_strdup(s);
		if (ft_strcmp(p->key, "PWD") == 0)
			p->data = ft_strdup(path);
		p = p->next;
	}
}
char	*get_user(t_env *lst)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, "USER") == 0)
			return (lst->data);
		lst = lst->next;
	}
	return (NULL);
}


int 	__built__in__(t_env *lst,t_minishell *list,int i)
{

	if (ft_strcmp(list->all_cmds[0], "pwd") == 0 || ft_strcmp(list->all_cmds[0], "PWD")== 0)
		__pwd__(i,lst->fd[1],list->out_id);
	else if (ft_strcmp(list->all_cmds[0], "cd") == 0)
		__cd__(list->all_cmds[1], lst);
	else if  (ft_strcmp(list->all_cmds[0], "echo") == 0|| ft_strcmp(list->all_cmds[0], "ECHO")== 0)
		__echo__(list,i,lst->fd[1],list->out_id);
	else if (ft_strcmp(list->all_cmds[0], "env") == 0|| ft_strcmp(list->all_cmds[0], "ENV")== 0)
	{
		if(check_env(lst) == NULL)
		{
			write(2, "env: No such file or directory\n", 31);
			return (0);
		}
		__print__env__(lst,i,lst->fd[1],list->out_id);
	}
		
	else if (ft_strcmp(list->all_cmds[0], "export") == 0|| ft_strcmp(list->all_cmds[0], "EXPORT")== 0)
	{
		__add__to__export__(lst, list);
		if (list->all_cmds[1] == NULL)
			__print__export__(lst,i,lst->fd[1],list->out_id);
	}
	else if  (ft_strcmp(list->all_cmds[0], "exit") == 0 || ft_strcmp(list->all_cmds[0], "EXIT") == 0)
	{
		printf("exit\n");
		s = 0;
		exit(0);
	}
	else if  (ft_strcmp(list->all_cmds[0], "unset") == 0|| ft_strcmp(list->all_cmds[0], "UNSET") == 0)
		__unset__(lst, list);
	else 
		return(1);
	return (0);
	//This is the way !!
}
