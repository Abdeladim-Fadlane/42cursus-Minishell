/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:07:17 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/14 15:26:28 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(char *s, char *d)
{
	t_env	*list;
	//printf("%s\n", s);
	list = (t_env *)malloc(sizeof(t_env));
	list->data = d;
	list->key = s;
	list->next = NULL;
	return (list);
}


t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	if (!lst)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

// t_env	*ft_lstlastt(t_env *lst)
// {
// 	if (lst)
// 	{
// 		while (lst->next)
// 			lst = lst->next;
// 	}
// 	return (lst);
// }

// void	add_back(t_env *lst, t_env *new)
// {
// 	if (!new)
// 		return ;
// 	if (!lst)
// 	{
// 		lst = new;
// 		return ;
// 	}
// 	ft_lstlastt(lst)->next = new;
// }

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
int	lstsize(t_minishell *list)
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
int	ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}