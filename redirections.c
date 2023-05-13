/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:48:39 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/09 11:15:36 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(t_content *content)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (content->type == OUT || content->type == APE)
	{
		if (content->type == OUT)
			new->type = OUT;
		else
			new->type = APE;
		new->out = content->content;
	}
	if (content->type == INF)
	{
		new->in = content->content;
		new->type = INF;
	}
	if (content->type == DEL)
	{
		new->limiter = content->content;
		new->type = DEL;
	}
	new->next = 0;
	return (new);
}

t_redir	*ft_last(t_redir *l)
{
	if (!l)
		return (0);
	while (l->next)
		l = l->next;
	return (l);
}

void	add_redir(t_redir **lst, t_redir *new)
{
	t_redir	*tem;

	//printf ("type %d , str value %s\n", new->type,new->out);
	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		tem = ft_last(*lst);
		tem->next = new;
	}
}
