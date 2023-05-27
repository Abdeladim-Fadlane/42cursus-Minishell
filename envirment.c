/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:17:12 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/17 16:01:57 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**array_env(char **env, int j)
{
	char **p;
	int i;
	int k;
	int len;

	len = 0;
	i = 0;
	k = 0;
	p = malloc(sizeof(char *) * 3);
	while (env[j][i] != '=')
		i++;
	while (env[j][len])
		len++;
	p[0] = ft_substr(env[j], 0, i);
	p[1] = ft_substr(env[j], i + 1, len);
	p[2] = NULL;
	return (p);
}

int     len_env(char **en)
{
    int     i;
    
    i = 0;
    while (en[i])
        i++;
    return (i);
}

t_env   *ft_lstnew_env(char *s1, char *s2)
{
    t_env   *env;

    env = malloc(sizeof(t_env));
    env->key  = s1;
    env->data = s2;
    env->next = NULL;
    return (env);
}

t_env   *ft_last_env(t_env **list)
{
    t_env	*tmp;

	tmp = (*list);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void    ft_add_back_env(t_env **lst, t_env *new)
{
    t_env *tem;
    
    if (!*lst)
        *lst = new;
    else
    {
        tem = ft_last_env(lst);
        tem->next = new;
    }
}