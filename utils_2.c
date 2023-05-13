/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 20:22:41 by marvin            #+#    #+#             */
/*   Updated: 2023/04/19 20:22:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_strdup(const char *source)
// {
// 	char	*mem;
// 	int		i;
	
// 	i = 0;
// 	mem = malloc((ft_strlen(source) + 1) * sizeof(char));
// 	if (!mem)
// 		return (NULL);
// 	while (source[i] != '\0')
// 	{
// 		mem[i] = source[i];
// 		i++;
// 	}
// 	mem[i] = '\0';
// 	return (mem);
// }

// int ft_strlen(const char *s)
// {
//     int i;

//     i = 0;
//     while (s[i])
//         i++;
//     return i;
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*mem;
// 	size_t	lengthstring;
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	lengthstring = ft_strlen(s);
// 	if (!s[start] || start >= lengthstring || len == 0)
// 		return (ft_strdup(""));
// 	if (len > (lengthstring - start))
// 		len = lengthstring - start;
// 	mem = malloc(len + 1);
// 	if (!mem)
// 		return (NULL);
// 	while (len > i && s[start] != '\0')
// 		mem[i++] = s[start++];
// 	mem[i] = '\0';
// 	return (mem);
// }


int	check(char const *set, char s)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
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
// 	//free(s1);
// 	return (mem);
// }

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
