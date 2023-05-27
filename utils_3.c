/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:56:43 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/26 14:47:28 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_v2(char *s)
{
	int	i;

	i = 0;
	if (ft_strcmp(s, "<") || ft_strcmp(s, "<<") || ft_strcmp(s, "<")
		|| ft_strcmp(s, "<<"))
		return (1);
	return (0);
}

int	content_count(char **s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		count++;
		i++;
	}
	return (count);
}

void	ft_intial_new(t_minishell *new, int index, int pipe, char **str)
{
	new->s1 = malloc(sizeof(char *) * content_count(str) + 1);
	if (!new->s1)
		exit(1);
	new->redirct = 0;
	new->cmd = 0;
	new->pipe = pipe;
	new->next = NULL;
	new->index = index;
}

t_minishell	*ft_lstneww(char *s, int index, int pipe, t_env *env)
{
	t_minishell	*new;
	t_content	*content;
	char		**str;
	int			i;

	new = malloc(sizeof(t_minishell));
	i = 0;
	str = ft_split_parse(s, ' ');
	ft_intial_new(new, index, pipe, str);
	if (!str)
		exit(1);
	while (str[i])
	{
		content = pars_w(str[i], 0, env, 0); // to expand if we need to like exmple (s1[i] == $USER --> ayylaaba).
		new->s1[i] = content->content;
		if (!ft_strcmp(new->s1[i], "<"))
			add_redir(&new->redirct, new_redir(pars_w(str[++i], INF, env, 0)));
		else if (!ft_strcmp(new->s1[i], ">"))
			add_redir(&new->redirct, new_redir(pars_w(str[++i], OUT, env, 0)));
		else if (!ft_strcmp(new->s1[i], "<<"))
			add_redir(&new->redirct, new_redir(pars_w(str[++i], DEL, env, 1))); // we don't need to expand what after delimiter that's why i useed last arg 1 
		else if (!ft_strcmp(new->s1[i], ">>"))
			add_redir(&new->redirct, new_redir(pars_w(str[++i], APE, env, 0)));
		else if (check_redir_v2(content->content) == 1)
			add_back_cmd(&new->cmd, new_cmd(content->content));
		free(content);
		i++;
	}
	new->all_cmds = pass_cmds(new->cmd); // we store all cmds to each token if we find it.
	//ft_free(new->s1);
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
		*lst = addnew;
	else
	{
		tem = ft_last_shell(*lst);
		tem->next = addnew;
	}
}
