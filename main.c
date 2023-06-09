/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:15 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/09 11:49:41 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_delmiter(char *h)
{
	int		i;
	char	*str;

	str = ft_strtrim(h, " ");
	i = 0;
	if ((str[0] == '\"' && str[ft_strlen(h) - 1] == '\"') || (str[0] == '\''
			&& str[ft_strlen(h) - 1] == '\''))
		return (1);
	return (0);
}

int	__main(t_minishell *list)
{
	if (list->redirct->type == INF)
	{
		if (open_infile(list->redirct->in, list) == 1)
			return (0);
		free(list->redirct->in);
	}
	if (list->redirct->type == OUT)
	{
		if (open_outfile(list->redirct->out, list) == 1)
			return (0);
		free(list->redirct->out);
	}
	return (1);
}

void	__main__(t_env *lst, t_minishell *list)
{
	t_minishell	*p;
	t_object	*obj;

	p = list;
	obj = NULL;
	while (list)
	{
		list->out_id = -1;
		while (list->redirct)
		{
			if (__main(list) == 0)
				return ;
			if (list->redirct->type == APE)
				if (open_append(list->redirct->out, list) == 1)
					return ;
			if (list->redirct->type == DEL)
			{
				t_lstadd_back(&obj, t_lstnew(list->redirct->limiter));
				lst->n = 1;
			}
			list->redirct = list->redirct->next;
		}
		list = list->next;
	}
	pipex(p, lst, obj);
}
