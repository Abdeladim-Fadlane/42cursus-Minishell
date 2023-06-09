/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deatch_redirc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/05/22 20:48:30 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/22 20:48:30 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_redir(char s1, char s2, int *count, int *i)
{
	if ((s1 == '<' && s2 == '<') \
			|| (s1 == '>' && s2 == '>'))
	{
		*count += 1;
		*i += 2;
	}
	else if ((s1 == '>' || s1 == '<'))
	{
		*count += 1;
		*i += 1;
	}
}

int	all_redric(char *src, int i, int count)
{
	char ch;

	while (src[i])
	{
		count_redir(src[i], src[i + 1], &count, &i);
		if (src[i] == '\'' || src[i] == '\"')
		{
			ch = src[i++];
			while (src[i] && (src[i] != '\'' || src[i] != '\"'))
			{
				count_redir(src[i], src[i + 1], &count, &i);	
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

int	handle_single(char c, char *line, int i)
{
	line[i++] = ' ';
	line[i++] = c;
	line[i++] = ' ';
	return (i);
}

int	hande_double(char c, char *line, int i)
{
	line[i++] = ' ';
	line[i++] = c;
	line[i++] = c;
	line[i++] = ' ';
	return (i);
}

void	detach_rediec(char *str, char *line, int i, int j)
{

	int s;
	int d;

	s = 0;
	d = 0;
	while (str[i])
	{
		if (line[i] == '\'' && d == 0 && s == 0)
			s = 1;
		else if (line[i] == '\'' && d == 0 && s == 1)
			s = 0;
		else if (line[i] == '\"' && s == 0 && d == 0)
			d = 1;
		else if (line[i] == '\"' && s == 0 && d == 1)
			d = 0;
		if (d == 0 && s == 0 && (str[i] == '>' && str[i + 1] == '>'))
		{
			j = hande_double(str[i], line, j);
			i += 2;
		}
		else if (d == 0 && s == 0 && (str[i] == '<' && str[i + 1] == '<'))
		{
			j = hande_double(str[i], line, j);
			i += 2;
		}
		else if (d == 0 && s == 0 && (str[i] == '>' || str[i] == '<'))
		{
			j = handle_single(str[i], line, j);
			i++;
		}
		else
			line[j++] = str[i++];
	}
	line[j] = '\0';
}