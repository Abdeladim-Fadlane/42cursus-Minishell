/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:42:11 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/25 22:18:28 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*ptr;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	len = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	ptr = malloc(sizeof(char) * len);
// 	if (ptr == NULL)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	len = 0;
// 	while (s2[len])
// 	{
// 		ptr[i++] = s2[len++];
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);  
}
