/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/05/22 20:49:42 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/22 20:49:42 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_space(char *s, int k)
{
	if (k == 1)
	{
		if ((*s == '>' && ft_strrchr_v2(s + 1, ' ') == 1) || *s == '<'
			|| (*s == '>' && *s + 1 == '>') || ft_strrchr_v2(s,
				' ') == 1)
			return (1);
	}
	else
	{
		if ((*s == '<' && ft_strrchr_v2(s + 1, ' ') == 1) || *s == '>'
			|| (*s == '<' && *s + 1 == '<') || ft_strrchr_v2(s,
				' ') == 1)
			return (1);
	}
	s++;
	while (*s && *s == ' ')
		s++;
	if (*s == '|')
		return (1);
	return (0);
}

int	check_redir(char *s, int i)
{
	while (s[++i])
	{
		if (s[i] == '>')
		{
			i++;
			if (check_pipe_space(s + i, 1) == 1)
				return (1);
		}
		if (s[i] == '<')
		{
			if (check_pipe_space(s + i, 0) == 1)
				return (1);
		}
	}
	return (0);
}

int	handle_pipe(char *str, int i)
{
	char	ch;
	char	*h;

	h = ft_strtrim(str, " ");
	if (h[0] == '|' || h[ft_strlen(h) - 1] == '|')
		return (free(h), 1);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ch = str[i++];
			while (str[i] && str[i] != ch)
				i++;
		}
		if (str[i] == '|' && str[i + 1] == '|')
			return (1);
		if (str[i] == '|')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == '|')
				return (1);
		}
	}
	return (free(h), 0);
}

int	qotes_syntext(char *line, int d, int s)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' && d == 0 && s == 0)
			s = 1;
		else if (line[i] == '\'' && d == 0 && s == 1)
			s = 0;
		else if (line[i] == '\"' && s == 0 && d == 0)
			d = 1;
		else if (line[i] == '\"' && s == 0 && d == 1)
			d = 0;
	}
	if (s == 1 || d == 1)
		return (404);
	return (0);
}

int	check_syntext(char *line)
{
	int	i;

	i = -1;
	if (qotes_syntext(line, 0, 0) == 404)
		return (404);
	if (handle_pipe(line, -1) == 1 || check_redir(line, -1) == 1)
		return (404);
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			i++;
			while (line[i] && line[i] == ' ')
				i++;
		}
		if ((line[i] == '>' || line[i] == '<') && line[i - 1] == ' ')
			return (404);
	}
	return (0);
}
