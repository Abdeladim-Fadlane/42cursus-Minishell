/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:15 by afadlane          #+#    #+#             */
/*   Updated: 2023/04/14 18:07:32 by afadlane         ###   ########.fr       */
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
// int		export_parcing(char *s)
// {
// 	if()
// }

// void	add_to_export(t_env *lst, char *s)
// {
// 	int  i =0;
// 	int j = 1;
// 	char **p = ft_split(s,' ');
// 	while(p)
// 		i++;
// 	while(j++ < i)
// 	{
// 		if(export_parcing(p[j]))
// 	}
// 	if(p[1] == NULL)
// 		return;
// 	char **ptr = ft_split(p[1],'=');
// 	add_back(&lst,ft_lstnew(ptr[0],ptr[1]));
// }

int	main(int ac, char **av, char **env)
{

	t_env *lst;
 	char	**p;
	int j = 0;
   


   
	while (j < get_len(env))
	{
		p = split_pwd(env, j);
		add_back(&lst,ft_lstnew(p[0],p[1]));
		j++;
	}
	ft_readline(lst,ac,av);
}