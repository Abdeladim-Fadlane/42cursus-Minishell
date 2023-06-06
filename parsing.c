/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/05/22 20:49:17 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/22 20:49:17 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str(char *src, char c)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim_parse(char *str, char *s)
{
	int		i;
	char	*k;
	int		len;

	i = 0;
	len = ft_strlen(str) - 1;
	while (str[i] && check_str(str, s[i]))
		i++;
	while (check_str(str, s[len]))
		len--;
	k = ft_substr(str, i, len - i + 1);
	return (k);
}

t_minishell	*parsing(char **s, t_env *env)
{
	t_minishell	*new;
	t_minishell	*fullshell;
	int			pipe;
	int			i;

	i = 0;
	(void)env;
	new = 0;
	fullshell = 0;
	while (s[i])
	{
		if (s[i + 1])
			pipe = PIPE;
		else
			pipe = 0;
		new = ft_lstneww(s[i], i, pipe, env);
		ft_add_back(&fullshell, new);
		i++;
	}
	return (fullshell);
}
