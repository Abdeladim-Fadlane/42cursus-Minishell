/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:15 by afadlane          #+#    #+#             */
/*   Updated: 2023/04/14 01:10:24 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	sort_export(t_env *tmp, int (*ft_strcmp) (char *, char *))
{
	t_env	*lst;
	char	*swap;
	char	*swap1;

	lst = tmp;
	while (tmp && tmp->next)
	{
		if (((*ft_strcmp)((tmp)->key, (tmp)->next->key)) > 0)
		{
			swap = (tmp)->data;
			(tmp)->data = (tmp)->next->data;
			(tmp)->next->data = swap;
			swap1 = (tmp)->key;
			(tmp)->key = (tmp)->next->key;
			(tmp)->next->key = swap1;
			(tmp) = lst;
		}
		else
			(tmp) = (tmp)->next;
	}
	(tmp) = lst;
	
}


void	add_to_export(t_env *lst, char *s)
{
	char **p = ft_split(s,' ');
	if(p[1] == NULL)
		return;
	char **ptr = ft_split(p[1],'=');
	add_back(&lst,ft_lstnew(ptr[0],ptr[1]));
}

int	main(int ac, char **av, char **env)
{
	t_env *lst;

	int j = 0;
	char	**p;
	while (j < get_len(env)-1)
	{
		p = split_pwd(env, j);
		add_back(&lst,ft_lstnew(p[0],p[1]));
		j++;
	}
	ft_readline(lst,ac,av);
}