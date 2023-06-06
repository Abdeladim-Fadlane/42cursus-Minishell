/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:42:11 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/06/06 16:38:18 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinn(char *s1, char *s2)
{
	char	*ptr;
	int		len;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = malloc(sizeof(char) * len);
	if (ptr == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	len = 0;
	while (s2 && s2[len])
	{
		ptr[i] = s2[len];
		i++;
		len++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// char	*ft_strcpy(char *dest, char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

int	is_valid(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

// int	ft_isdigit(int c)
// {
// 	if (c >= 48 && c <= 57)
// 		return (1);
// 	else
// 		return (0);
// }

t_minishell	*ft_last_shell(t_minishell *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}
