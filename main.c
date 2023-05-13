/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:15 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/14 00:03:17 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_erorrs(char *s)
{
	if (ft_isalpha(s[0]) == 0)
	{
		printf("export : %s not a valid identifier\n", s);
		exit(1);
	}
}

int	__check_key_exit(t_env *lst, char *s)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, s) == 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void	expand_data(t_env *lst, char **s)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, s[0]) == 0)
		{
			if (ft_strcmp(lst->data, s[1]))
				lst->data = ft_strdup(s[1]);
		}
		lst = lst->next;
	}
}

int	__check_add(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

void	__check_data_exit(t_env *lst, char **s, int flag)
{
	char	*d;

	while (lst)
	{
		if (ft_strcmp(lst->key, ft_split(s[0], '+')[0]) == 0)
		{
			if (flag == 0)
			{
				if(lst->data == NULL)
					lst->data = s[1];
				else
				{
					d = lst->data;
					lst->data = ft_strjoin(d, s[1]);
				}
			}
			else if (flag)
				lst->data = s[1];
		}
		lst = lst->next;
	}
	
}

void	__add__to__export__(t_env *lst, char *s)
{
	char	**p;
	int		flag;
	int		j;
	char	**ptr;
	char	*str;

	p = ft_split(s, ' ');
	if (p[1] == NULL)
		return ; 
	j = 1;
	while (p[j])
	{
		flag = 1;
		check_erorrs(p[j]);
		ptr = ft_split(p[j], '=');
		str = ft_split(ptr[0], '+')[0];
		if (__check_key_exit(lst, str))
			ft_lstadd_back(&lst, ft_lstnew(str, ptr[1]));
		if (__check_add(ptr[0]) == 0)
			flag = 0;
		__check_data_exit(lst, ptr, flag);
		
		j++;
	}
}

void	__main__(t_env *lst, char **env,t_minishell *list,char *buff)
{

	//(void)buff;
	if (list->next == NULL)
		__built__in__(lst, buff,env,list);
	// print_data(list);
	// pipex(list,lst,env);
}
