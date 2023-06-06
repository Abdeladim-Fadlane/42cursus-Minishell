/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/05/22 20:49:30 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/22 20:49:30 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_strdup(char *source)
// {
// 	int		i;
// 	char	*mem;

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

// int	ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s && s[i])
// 		i++;
// 	return (i);
// }

// char	*ft_substr(char *s, unsigned int start, size_t len)
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

int	check(char *set, char s)
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

char	*remove_quotes(char *str, int i, int s, int d)
{
	char	*ptr;
	int		k;

	ptr = malloc((ft_strlen(str) + 1) * sizeof(char));
	k = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && d == 0 && s == 0)
			s = 1;
		else if (str[i] == '\'' && d == 0 && s == 1)
			s = 0;
		else if (str[i] == '\"' && s == 0 && d == 0)
			d = 1;
		else if (str[i] == '\"' && s == 0 && d == 1)
			d = 0;
		else
			ptr[k++] = str[i];
		i++;
	}
	return (free(str), ptr[k] = '\0', ptr);
}
