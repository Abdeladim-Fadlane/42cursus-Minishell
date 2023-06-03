/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:23 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/03 14:41:43 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_export(t_env *lst, t_minishell *list, int i)
{
	__add__to__export__(lst, list);
	if (list->all_cmds[1] == NULL)
		__print__export__(lst, i, lst->fd[1], list->out_id);
}

int	ft_env(t_env *lst, t_minishell *list, int i)
{
	g_sig->sst = 0;
	if (list->all_cmds[1] != NULL)
	{
		write(2, "env: with no options or arguments\n", 35);
		g_sig->sst = 127;
		return (0);
	}
	if (check_env(lst) == NULL)
	{
		write(2, "env: No such file or directory\n", 31);
		g_sig->sst = 127;
		return (0);
	}
	__print__env__(lst, i, lst->fd[1], list->out_id);
	return (1);
}

int	__built__in__(t_env *lst, t_minishell *list, int i)
{
	ft_exit(list);
	if (ft_strcmp(list->all_cmds[0], "pwd") == 0 || ft_strcmp(list->all_cmds[0],
			"PWD") == 0)
		__pwd__(i, lst->fd[1], list->out_id);
	else if (ft_strcmp(list->all_cmds[0], "cd") == 0)
		__cd__(list->all_cmds[1], lst);
	else if (ft_strcmp(list->all_cmds[0], "echo") == 0
			|| ft_strcmp(list->all_cmds[0], "ECHO") == 0)
		__echo__(list, i, lst->fd[1], list->out_id);
	else if (ft_strcmp(list->all_cmds[0], "env") == 0
			|| ft_strcmp(list->all_cmds[0], "ENV") == 0)
		ft_env(lst, list, i);
	else if (ft_strcmp(list->all_cmds[0], "export") == 0
			|| ft_strcmp(list->all_cmds[0], "EXPORT") == 0)
		ft_export(lst, list, i);
	else if (ft_strcmp(list->all_cmds[0], "unset") == 0
			|| ft_strcmp(list->all_cmds[0], "UNSET") == 0)
		__unset__(lst, list);
	else
		return (1);
	return (0);
}
