/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:52 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/10 09:18:26 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*charge_str(char c, char *src)
{
	char	*src1;
	int		i;

	src1 = malloc(ft_strlen(src) + 2);
	i = 0;
	while (src[i])
	{
		src1[i] = src[i];
		i++;
	}
	src1[i] = c;
	i++;
	src1[i] = '\0';
	return (src1);
}

char	*expand(char *s, int type, char *str)
{
	int	i;

	(void)type;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
			{
				str = charge_str(s[i], str);
				i++;
			}
		}
		else
			str = charge_str(s[i], str);
		i++;
	}
	return (str);
}

int	single_q(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '\'' && s[ft_strlen(s) - 1] == '\'')
		return (1);
	else if (s[0] == '\"' && s[ft_strlen(s) - 1] == '\"')
		return (2);
	else
		return (0);
}

char	*remove_single(char *s, char c)
{
	int		i;
	int		j;
	char	*src;

	j = 0;
	i = 0;
	src = malloc(sizeof(char) * ft_strlen(s) - count_char(s, c));
	if (!src)
		return 0;
	while (s[i])
	{
		if (s[i] != c)
			src[j++] = s[i];
		i++;
	}
	src[j] = '\0';
	return (src);
}

t_content	*pars_w(char *s, int type)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	if (single_q(s) == 1)
	{
		content->content = expand(s, 0, ft_strdup(""));
		content->content = remove_single(content->content, '\'');
	}
	if (single_q(s) == 2)
	{
		content->content = expand(s, 0, ft_strdup(""));
		content->content = remove_single(content->content, '\"');
	}
	else
		content->content = expand(s, type, ft_strdup(""));
	content->type = type;
	return (content);
}
