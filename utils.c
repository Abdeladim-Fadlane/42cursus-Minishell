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

int	count_char(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}

	return (count);
}

int	check_qouts(char *line, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == c)
			count++;
		i++;
	}
	return (count % 2);
}

int	aft_strrchr(const char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}

int	check_redir(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>')
		{
			i++;
			if ((s[i] == '>' && aft_strrchr(s + i + 1, ' ') == 1) || s[i] == '<'
				|| (s[i] == '>' && s[i + 1] == '>') || aft_strrchr(s + i,
					' ') == 1)
				return (1);
			else
			{
				while (s[i] && s[i] == ' ')
					i++;
				if (s[i] == '|')
					return (1);
			}
		}
		if (s[i] == '<')
		{
			i++;
			if ((s[i] == '<' && aft_strrchr(s + i + 1, ' ') == 1) || s[i] == '>'
				|| (s[i] == '<' && s[i + 1] == '<') || aft_strrchr(s + i,
					' ') == 1)
				return (1);
			else
			{
				while (s[i] && s[i] == ' ')
					i++;
				if (s[i] == '|')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	handle_pipe(char *str)
{
	int i;
	char ch;
	char *h;

	i = 0;
	h = ft_strtrim(str, " ");
	if (h[0] == '|' || h[ft_strlen(h) - 1] == '|')
	{
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ch = str[i];
			i++;
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
		i++;
	}
	return (0);
}

int	check_syntext(char *line)
{
	int i;
	int k;
	int d;
	int s;

	i = 0;
	d = 0;
	s = 0;
	k = 0;

	while (line[i])
	{
		if (line[i] == '\'' && d == 0 && s == 0)
			s = 1;
		else if (line[i] == '\'' && d == 0 && s == 1)
			s = 0;
		else if (line[i] == '\"' && s == 0 && d == 0)
			d = 1;
		else if (line[i] == '\"' && s == 0 && d == 1)
			d = 0;
		i++;
	}
	if (s == 1 || d == 1)
		return (404);
	i = 0;
	if (handle_pipe(line) == 1)
		return (404);
	if (check_redir(line) == 1) // redir problems "<<<" or "<>".
		return (404);
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			i++;
			while (line[i] && line[i] == ' ')
				i++;
		}
		if ((line[i] == '>' || line[i] == '<') && line[i - 1] == ' ')
			// if we find beteween redir space < <.
			return (404);
		if (line[i])
			i++;
	}
	return (0);
}
