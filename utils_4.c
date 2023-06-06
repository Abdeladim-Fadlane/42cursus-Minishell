/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:52 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/06/06 15:02:24 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*charge_str(char c, char *src)
{
	char	*src1;
	int		i;

	src1 = malloc(ft_strlen(src) + 2);
	i = 0;
	while (src && src[i])
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

void	get_data(t_env *env, char *key, char **s, int *k)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			*s = ft_strdup(env->data);
			*k = 1;
		}
		env = env->next;
	}
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
	if (s1[0] == '$' && s1[1] == '?')
	{
		s2 = ft_itoa(g_sig->status);
		s3 = ft_strjoinn(str, s2);
		*i += 2;
		return (free(s2), s3);
	}
	while (s1 && s1[k] && is_valid(s1[k]))
		k++;
	*i += k;
	key = ft_substr(s1, 0, k);
	get_data(env, key, &s2, &k);
	if (k != 1)
		s2 = ft_strdup("");
	s3 = ft_strjoinn(str, s2);
	free(str);
	return (free(s2), free(key), s3);
}

void	check_close_qotes(char *s, int *d, int *ss)
{
	if (*s == '\'' && *d == 0 && *ss == 0)
		*ss = 1;
	else if (*s == '\'' && *d == 0 && *ss == 1)
		*ss = 0;
	else if (*s == '\"' && *ss == 0 && *d == 0)
		*d = 1;
	else if (*s == '\"' && *ss == 0 && *d == 1)
		*d = 0;
}

char	*expand(char *s, char *str, t_env *env, int j)
{
	int		i;

	i = 0;
	env->d = 0;
	env->ss = 0;
	if (!s || !s[0])
		return (NULL);
	while (s[i])
	{
		check_close_qotes(s + i, &env->d, &env->ss);
		if (s[i] == '$' && s[i + 1] == '?')
			str = env_value(s + i, str, env, &i);
		else if ((s[i] == '$' && !s[i + 1]) || ft_strrchr(s + i, ' '))
			str = charge_str(s[i++], str);
		else if (s[i] == '$' && !is_valid(s[i + 1]))
			str = charge_str(s[i++], str);
		else if (s[i] == '$' && ft_isdigit(s[i + 1]) == 1)
			i++;
		else if (s[i] == '$' && env->ss == 0 && j != 1)
			str = env_value(s + ++i, str, env, &i);
		else
			str = charge_str(s[i++], str);
	}
	return (str);
}
