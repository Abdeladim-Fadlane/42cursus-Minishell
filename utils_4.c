/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:52 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/25 16:36:46 by ayylaaba         ###   ########.fr       */
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
	free(src);
	return (src1);
}

char	*remove_quotes(char *str)
{
	char	*ptr;
	int		i;
	int		k;
	int		d;
	int		s;

	ptr = malloc((ft_strlen(str) + 1) * sizeof(char));
	d = 0;
	s = 0;
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\'' && d == 0 && s == 0)
			s = 1;
		else if (str[i] == '\'' && d == 0 && s == 1)
			s = 0;
		else if (str[i] == '\"' && s == 0 && d == 0)
			d = 1;
		else if (str[i] == '\"' && s == 0 && d == 1)
			d = 0;
		else
			ptr[k++] = str[i];
		i++;
	}
	ptr[k] = '\0';
	return (ptr);
}

int	is_valid(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

char	*env_value(char *s1, char *str, t_env *env, int *i)
{
	char	*key;
	char	*s2;
	char	*s3;
	int		k;

	s2 = NULL;
	s3 = NULL;
	k = 0;

	while (s1[k] && is_valid(s1[k]))
		k++;
	*i += k;
	key = ft_substr(s1, 0, k);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			s2 = ft_strdup(env->data);
			k = 1;
		}
		env = env->next;
	}
	if (k != 1)
		s2 = ft_strdup("");
	s3 = ft_strjoin(str, s2);

	return (s3);
}

char	*expand(char *s, char *str, t_env *env, int j)
{
	int	d;
	int	ss;
	int	i;
	int	k;

	i = 0;
	if (!s || !s[0])
		return (NULL);
	d = 0;
	ss = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
			
		if ((s[i] == '$' && !s[i + 1]) || ft_strrchr(s + i, ' '))
			str = charge_str(s[i], str);
		if (s[i] == '\'' && d == 0 && ss == 0)
			ss = 1;
		else if (s[i] == '\'' && d == 0 && ss == 1)
			ss = 0;
		else if (s[i] == '\"' && ss == 0 && d == 0)
			d = 1;
		else if (s[i] == '\"' && ss == 0 && d == 1)
			d = 0;
		if (s[i] == '$' && ss == 0 && j != 1) // we Don't expand if the env varible come after delmiter(j != 1) and if befor env varible ' .
			str = env_value(s + ++i, str, env, &i);
		else
			str = charge_str(s[i++], str);
	}
	return (str);
}

t_content	*pars_w(char *s, int type, t_env *env, int j)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	content->content = expand(s, ft_strdup(""), env, j); // we hold the string with expand if possible.
	content->content = remove_quotes(content->content); // we remove the quots the most to remove.
	content->type = type; // type of each redrict.
	return (content);
}
