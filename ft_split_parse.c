/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/05/22 20:48:48 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/22 20:48:48 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	word_len(char *s, char c)
{
	int i;
	char ch;

	i = 0;
	while (s[i] && s[i] != c)
	{
		if ((c == ' ' && (s[i] == '\'' || s[i] == '\"')) || (s[i] == '\'' || s[i] == '\"'))
		{
			ch = s[i++];
			while (s[i] && s[i] != ch)
			{
				i++;
			}
		}
		if (s[i])
			i++;
	}
	return (i);
}

char	*full_charge(char *s, char c)
{
	int i;
	char *w;
	int len;

	i = 0;
	len = word_len(s, c);
	w = malloc(len + 1);
	while (i < len)
	{
		w[i] = s[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

char	**ft_charge(char **s, char *s1, char c)
{
	int j;
	int start;
	int i;
	char ch;

	j = 0;
	i = 0;
	start = -1;
	while (s1[i])
	{
		// if (/*(c == ' ' && (s1[i] == '\'' || */((s1[i] == '\"')) || (s1[i] == '\''
		// 			|| s1[i] == '\"'))
		// {
		// 	ch = s1[i];
		// 	start = i;
		// 	i++;
		// 	while (s1[i] && s1[i] != ch)
		// 		i++;
		// }
		if (s1[i] != c && start < 0)
		{
			start = i;
			if (s1[i] == '\'' || s1[i] == '\"')
			{
				ch = s1[i];
				i++;
				while (s1[i] && s1[i] != ch)
					i++;
			}
		}
		if (((s1[i] == c || i == ft_strlen(s1) - 1) && start >= 0))
		{
			s[j] = full_charge((s1 + start), c);
			start = -1;
			if (!s[j])
				return (ft_free(s), NULL);
			j++;
		}
		i++;
	}
	s[j] = NULL;
	return (s);
}

int	count_strs(char *str, char c)
{
	int i;
	int num;
	char ch;

	i = 0;
	num = 1; // i intiall by 1 becouse str is not empty
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			num++;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			ch = str[i];
			i++;
			while (str[i] && str[i] != ch)
				i++;
		}
		if (str[i])
			i++;
	}
	return (num);
}

char	**ft_split_parse(char *str, char c)
{
	int i;
	char **s;

	i = 0;
	if (!str || !str[0])
		return (NULL);
	s = malloc(sizeof(char *) * (count_strs(str, c) + 1));
	if (!s)
		return (NULL);
	s = ft_charge(s, str, c);
	return (s);
}
