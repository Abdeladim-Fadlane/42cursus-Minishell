/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 09:56:12 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/06/09 11:32:18 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	ft_lenght(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int m)
{
	int			len;
	char		*p;
	long long	n;

	n = m;
	len = ft_lenght(n);
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	p[len] = '\0';
	if (n < 0)
	{
		p[0] = '-';
		n = n * -1;
	}
	if (n == 0)
		p[0] = '0';
	while (n > 0)
	{
		p[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (p);
}

int	check_redir_v2(char *s)
{
	int	i;

	i = 0;
	if (ft_strcmp(s, "<") || ft_strcmp(s, "<<") || ft_strcmp(s, "<")
		|| ft_strcmp(s, "<<"))
		return (1);
	return (0);
}

int	content_count(char **s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	skip_qoute(char *s, int *i, int k)
{
	if (k == 0)
	{
		if (!s[*i])
			return (1);
	}
	else
	{
		*i += 1;
		while (s[*i] && (s[*i] != '\'' && s[*i] != '\"'))
			*i += 1;
	}
	return (0);
}
