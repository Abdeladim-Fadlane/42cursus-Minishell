/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:36:17 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/09 11:30:43 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_get_cmd(char *lst, t_env *p)
{
	if (opendir(lst) != NULL)
	{
		write(2, lst, ft_strlen(lst));
		write(2, ": is a directory\n", 18);
		exit(126);
	}
	if (check_env(p) == NULL)
	{
		write(2, lst, ft_strlen(lst));
		write(2, ": No such file or directory\n", 28);
		exit(127);
	}
}

char	*get_cmd(char **ptr, char *lst, t_env *p)
{
	int		i;
	char	*buff;
	char	*t;

	i = 0;
	if (!lst || lst[0] == '\0')
		return (NULL);
	norm_get_cmd(lst, p);
	if (access(lst, 0) == 0)
		return (lst);
	while (ptr[i])
	{
		buff = ft_strjoin(ptr[i], "/");
		t = ft_strjoin(buff, lst);
		free(buff);
		if (access(t, X_OK) == 0)
			return (ffree(ptr, t));
		free(t);
		i++;
	}
	return (ffree(ptr, NULL));
}

int	addoldpwd(t_env *lst, int ac, char **av)
{
	(void)ac;
	(void)av;
	while (lst)
	{
		if (ft_strcmp(lst->key, "OLDPWD") == 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}
