/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:41:11 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/09 11:57:56 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

t_object	*t_lstnew(char *s)
{
	t_object	*list;

	list = (t_object *)malloc(sizeof(t_object));
	list->s = ft_strdup(s);
	list->next = NULL;
	return (list);
}

t_object	*t_lstlast(t_object *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	t_lstadd_back(t_object **lst, t_object *new)
{
	if (!lst)
		return ;
	if (*lst)
		t_lstlast(*lst)->next = new;
	else
		*lst = new;
}
