/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:56:43 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/10 23:02:39 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	go_to_parse(char **s, t_minishell *new)
{
	t_content	*content;
	int			i;

	i = 0;
	while (s[i])
	{
		content = pars_w(s[i], 0);
		// s[i] = content->content;
		if (!ft_strcmp(content->content, "<"))
			add_redir(&new->redirct, new_redir(pars_w(s[++i], INF)));
		else if (!ft_strcmp(content->content, ">"))
			add_redir(&new->redirct, new_redir(pars_w(s[++i], OUT)));
		else if (!ft_strcmp(content->content, "<<"))
			add_redir(&new->redirct, new_redir(pars_w(s[++i], DEL)));
		else if (!ft_strcmp(content->content, ">>"))
			add_redir(&new->redirct, new_redir(pars_w(s[++i], APE)));
		else
			add_back_cmd(&new->cmd, new_cmd(content->content));
		i++;
	}
}

t_minishell	*ft_lstneww(char *s, int index, int pipe)
{
	t_minishell	*new;
	char		**str;

	new = malloc(sizeof(t_minishell));
	new->redirct = 0;
	new->cmd = 0;
	str = ft_split_parse(s, ' ');
	if (!str)
		exit(1);
	//printf("token[%d]\n", index);
	//ft_print(str);
	go_to_parse(str, new);
	new->pipe = pipe;
	new->next = NULL;
	new->index = index;
	//printf ("i am here\n");
	new->all_cmds = pass_cmds(new->cmd);
	ft_free(str);
	return (new);
}

t_minishell	*ft_last_shell(t_minishell *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back(t_minishell **lst, t_minishell *addnew)
{
	t_minishell	*tem;

	if (!*lst)
	{
		*lst = addnew;
	}
	else
	{
		tem = ft_last_shell(*lst);
		tem->next = addnew;
	}
}
