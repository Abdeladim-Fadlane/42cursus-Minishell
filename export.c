/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:28:27 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/08 21:50:14 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			{
				free(lst->data);
				lst->data = ft_strdup(s[1]);
			}		
		}
		lst = lst->next;
	}
}

void	__check_data_exit(t_env *lst, char **s, int flag)
{
	char	*d;
	char **ptr;

	ptr = ft_split(s[0], '+');
	while (lst)
	{
		
		if (ft_strcmp(lst->key, ptr[0]) == 0)
		{
			if (flag == 0)
			{
				if (lst->data == NULL)
					lst->data = s[1];
				else
				{
					d = ft_strdup(lst->data);
					free(lst->data);
					lst->data = ft_strjoin(d, s[1]);
					free(d);
				}
			}
			else if (flag)
			{
				free(lst->data);
				lst->data = s[1];
			}
		}
		lst = lst->next;
	}
	ft_free(ptr);
}

void	__add__to__export__(t_env *lst, t_minishell *list, int j)
{
	if (list->all_cmds[1] == NULL)
		return ;
	while (list->all_cmds[j])
	{
		if (check_erorrs_export(list->all_cmds[j], "export") == 1)
			g_sig->sst = 1;
		else
		{
			lst->ptr = get_var(list->all_cmds[j]);
			norm_export(lst);
			if (__check_key_exit(lst, lst->p[0]))
			{
				if (check_flag(list->all_cmds[j]) == 1 && lst->ptr[1] == NULL)
					lst->s = ft_strdup("");
				else
					lst->s = ft_strdup(lst->ptr[1]);
				ft_lstadd_back(&lst, ft_lstnew(lst->p[0], lst->s));
				free(lst->s);
			}
			ft_free(lst->ptr);
			ft_free(lst->p);
		}
		j++;
	}
}
