/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:04:28 by afadlane          #+#    #+#             */
/*   Updated: 2023/04/09 20:15:11 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(char *d)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!d[0])
		return (NULL);
	while (d[i] != '\n' && d[i])
		i++;
	if (d[i] == '\0')
		ptr = malloc(i + 1);
	else
		ptr = malloc(i + 2);
	if (!ptr)
		return (NULL);
	i = 0;
	while (d[i] && d[i] != '\n')
	{
		ptr[i] = d[i];
		i++;
	}
	if (d[i] == '\n')
		ptr[i++] = '\n';
	ptr[i] = '\0';
	return (ptr);
}

char	*get_save_line(char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	ptr = ft_strdup(s + i + 1);
	free(s);
	return (ptr);
}

char	*get_read_line(int fd, char *container)
{
	char	*buff;
	int		i;

	i = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return ( NULL);
	while (!ft_strchr(container, '\n') && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			free(container);
			return (NULL);
		}
		buff[i] = '\0';
		container = ft_strjoin(container, buff);
		if (!container)
			return (NULL);
	}
	free(buff);
	return (container);
}

char	*get_next_line(int fd)
{
	static char	*container;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	container = get_read_line(fd, container);
	if (!container)
		return (NULL);
	buff = get_line(container);
	container = get_save_line(container);
	return (buff);
}
