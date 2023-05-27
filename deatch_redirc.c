/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deatch_redirc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:48:30 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/22 20:48:30 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"


int	all_redric(char *src)
{
	int i;
	int count;
	char ch;

	i = 0;
	count = 0;
	while (src[i])
	{
		if ((src[i] == '<' && src[i + 1] == '<') || (src[i] == '>' && src[i
				+ 1] == '>'))
		{
			count++;
			i += 2;
		}
		if ((src[i] == '>' || src[i] == '<'))
		{
			count++;
			i++;
		}
		else if (src[i] == '\'' || src[i] == '\"')
		{
			i++;
			ch = src[i];
			while (src[i] && src[i] != ch)
				i++;
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

void	detach_rediec(char *str, char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			j = hande_double(str[i], line, j);
			i += 2;
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			j = hande_double(str[i], line, j);
			i += 2;
		}
		else if (str[i] == '>' || str[i] == '<')
		{
			j = handle_single(str[i], line, j);
			i++;
		}
		else
			line[j++] = str[i++];
	}
	line[j] = '\0';
}
