/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:07:17 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/02 19:55:00 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"minishell.h"

t_env	*ft_lstnew(char *s,char *d)
{
	t_env	*list;

	list = (t_env *)malloc(sizeof(t_env));
	
	list->data = d;
    list->key = s;
	list->next = NULL;
	return (list);
}

t_env	*ft_lstlast(t_env **list)
{
	t_env	*tmp;

	tmp = (*list);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_back(t_env **list, t_env *new)
{
	t_env	*tmp;

	tmp = (*list);
	if ((*list) == NULL)
		*list = new;
	else if ((*list))
	{
		tmp = ft_lstlast(list);
		tmp->next = new;
	}
}

int	ft_lstsize(t_env *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}


int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	if(!s1 || !s2)
		return(1);
	while(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])	
		i++;
	return (s1[i] - s2[i]);
}