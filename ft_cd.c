/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:49:35 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/08 19:47:35 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_home(t_env *lst)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, "HOME") == 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void	more_cd(char *str, t_env *p, char *s)
{
	char	*s1;
	char	*d;
	char	*buff;
	char	path[1024];

	buff = getcwd(path, sizeof(path));
	s1 = ft_strjoin("/", str);
	d = ft_strjoin(buff, s1);
	if (chdir(d) != 0)
	{
		free(d);
		free(s1);
		g_sig->sst = 1;
		perror("cd ");
	}
	else
	{
		free(d);
		free(s1);
		buff = getcwd(path, sizeof(path));
		get_index_pwd(p, buff, s);
	}
}

void	norm_cd(char *str, t_env *p, char *s)
{
	char	path[1024];
	char	*buff;

	if (chdir(str) == 0)
	{
		buff = getcwd(path, sizeof(path));
		get_index_pwd(p, buff, s);
		return ;
	}
	else
		more_cd(str, p, s);
}

void	ft_cd(t_env *p, char *str, char *pathh)
{
	char	*buff;
	char	path[1024];

	buff = ft_strjoin("/Users/", get_user(p));
	if (chdir(buff) != 0)
	{
		free(buff);
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 28);
		g_sig->sst = 1;
	}
	else
	{
		free(buff);
		get_index_pwd(p, getcwd(path, sizeof(path)), pathh);
	}
}

void	__cd__(char *str, t_env *p)
{
	char	pathh[1024];

	getcwd(pathh, sizeof(pathh));
	if (!str && exit_home(p) == 1)
	{
		write(2, "afadlane$: cd : HOME not set\n", 30);
		g_sig->sst = 1;
	}
	if (!str)
		ft_cd(p, str, pathh);
	else if (ft_strcmp(pathh, str) == 0)
		return ;
	else
		norm_cd(str, p, pathh);
}
