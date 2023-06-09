/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:56:43 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/06/07 16:35:04 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int				i;
// 	unsigned char	*src1;
// 	unsigned char	*src2;

// 	src1 = (unsigned char *)s1;
// 	src2 = (unsigned char *)s2;
// 	i = 0;
// 	while ((src1[i] || src2[i]))
// 	{
// 		if (src1[i] != src2[i])
// 			return (src1[i] - src2[i]);
// 		i++;
// 	}
// 	return (0);
// }

void	delmi_app(t_minishell **new, char **s, char *str, t_env *env)
{
	if (!ft_strcmp(*s, "<"))
		add_redir(&(*new)->redirct, new_redir(pars_w(str, INF, env, 0)));
	else if (!ft_strcmp(*s, ">"))
		add_redir(&(*new)->redirct, new_redir(pars_w(str, OUT, env, 0)));
	else if (!ft_strcmp(*s, "<<"))
	{
		if (check_delmiter(str) == 1)
			g_sig->dude = 1;
		add_redir(&(*new)->redirct, new_redir(pars_w(str, DEL, env, 1)));
	}
	else if (!ft_strcmp(*s, ">>"))
		add_redir(&(*new)->redirct, new_redir(pars_w(str, APE, env, 0)));
}

void	ft_intial_new(t_minishell **new, int index, int pipe, char **s)
{
	(*new) = malloc(sizeof(t_minishell));
	if (!*new)
		return ;
	(*new)->str = ft_split_parse(*s, ' ');
	if (!(*new)->str)
		return ;
	(*new)->s1 = malloc(sizeof(char *) * content_count((*new)->str) + 1);
	if (!(*new)->s1)
		exit(1);
	(*new)->redirct = 0;
	(*new)->cmd = 0;
	(*new)->pipe = pipe;
	(*new)->index = index;
	(*new)->next = NULL;
}

t_minishell	*ft_lstneww(char *s, int index, int pipe, t_env *env)
{
	t_minishell	*new;
	t_content	*content;
	char		*str1;
	int			i;

	i = -1;
	ft_intial_new(&new, index, pipe, &s);
	while (new->str[++i])
	{
		content = pars_w(new->str[i], 0, env, 0);
		new->s1[i] = content->content;
		if (!ft_strcmp(new->s1[i], ">>") || !ft_strcmp(new->s1[i], "<<") || \
			!ft_strcmp(new->s1[i], "<") || !ft_strcmp(new->s1[i], ">"))
		{
			str1 = ft_strdup(new->s1[i]);
			free(new->s1[i]);
			delmi_app(&new, &str1, new->str[++i], env);
			free(str1);
		}
		else if (check_redir_v2(content->content) == 1)
			add_back_cmd(&new->cmd, new_cmd(content->content));
		free(content);
	}
	return (ft_free(new->str), new->all_cmds = pass_cmds(new->cmd), new);
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
