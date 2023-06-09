/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exutcutin_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:24:11 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/08 21:25:08 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_erorrs(char *s, char *d)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isalpha(s[i]) == 0)
		{
			g_sig->sst=1;
			printf("%s:`%s' not a valid identifier\n", d, s);
			return (1);
		}
		i++;
	}
	return (0);
}

int	norn_errors(char *s, char **p, char *d)
{
	if (!p[0] || s[0] == '=')
	{
		g_sig->sst = 1;
		printf("%s:`%s' not a valid identifier\n", d, s);
		ft_free(p);
		return (1);
	}
	return (0);
}

int	check_erorrs_export(char *s, char *d)
{
	char	**ptr;
	char	**p;
	int		i;

	i = 0;
	p = ft_split(s, '=');
	if (norn_errors(s, p, d) == 1)
		return (1);
	ptr = ft_split(p[0], '+');
	while (ptr[0][i])
	{
		if (ft_isalpha(ptr[0][i]) == 0)
		{
			printf("%s:`%s' not a valid identifier\n", d, s);
			ft_free(p);
			ft_free(ptr);
			return (1);
		}
		i++;
	}
	ft_free(p);
	ft_free(ptr);
	return (0);
}
