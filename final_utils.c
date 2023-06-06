/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:50:30 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/06/05 17:25:37 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_char(char *str, char c)
{
	int	i;
	int	count;

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
	int	i;
	int	count;

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

int	ft_strrchr_v2(const char *s, char c)
{
	int	i;
	int	count;

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

// char	*ft_strtrim(char *s1, char *set)
// {
// 	int		i;
// 	int		len;
// 	char	*mem;

// 	if (!s1 || !set)
// 		return (0);
// 	i = 0;
// 	len = ft_strlen(s1) - 1;
// 	while (s1[i] && check(set, s1[i]))
// 		i++;
// 	while (len > 0 && check(set, s1[len]))
// 		len--;
// 	mem = ft_substr(s1, i, len - i + 1);
// 	return (mem);
// }

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
