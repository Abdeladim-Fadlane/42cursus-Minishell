/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:48:39 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/06/06 14:00:57 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(t_content *content)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
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
	free(content);
	return (new->next = 0, new);
}

t_redir	*ft_last(t_redir *l)
{
	if (!l)
	{
		return (0);
	}
	while (l->next)
		l = l->next;
	return (l);
}

void	add_redir(t_redir **lst, t_redir *new)
{
	t_redir	*tem;

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

t_content	*pars_w(char *s, int type, t_env *env, int j)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	content->content = expand(s, NULL, env, j);
	content->content = remove_quotes(content->content, 0, 0, 0);
	content->type = type;
	return (content);
}
