/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:20:21 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/24 22:05:43 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__cd__(char *str, t_env *p)
{
	char	path[1024];
	char	pathh[1024];
	char	*buff;
	char	*s;

	s = getcwd(pathh, sizeof(pathh));
	if (!str)
	{
		if (chdir(ft_strjoin("/Users/", ft_strjoin("/", get_user(p)))) != 0)
			perror("cd ");
		get_index_pwd(p, getcwd(path, sizeof(path)), s);
	}
	else
	{
		buff = getcwd(path, sizeof(path));
		if (chdir(ft_strjoin(buff, ft_strjoin("/", str))) != 0)
			perror("cd ");
		get_index_pwd(p, getcwd(path, sizeof(path)), s);
	}
}

char	**__split__(char **env, int j)
{
	char	**p;
	int		i;
	int		k;
	int		len;

	len = 0;
	i = 0;
	k = 0;
	p = malloc(sizeof(char *) * 3);
	while (env[j][i] != '=')
		i++;
	len = i + 1;
	while (env[j][len])
		len++;
	p[0] = ft_substr(env[j], 0, i);
	p[1] = ft_substr(env[j], i + 1, len);
	p[2] = NULL;
	return (p);
}

void	__unset__(t_env *lst, t_minishell *ptr)
{
	int		i;
	t_env	*tmp;

	i = 1;
	while (lst->next)
	{
		while (ptr->all_cmds[i])
		{
			if (ft_strcmp(lst->next->key, ptr->all_cmds[i]) == 0)
			{
				tmp = lst->next->next;
				free(lst->next);
				lst->next = tmp;
			}
			if (lst->next == NULL)
				return ;
			i++;
		}
		i = 1;
		lst = lst->next;
	}
}

void	__pwd__(int k, int fd, int fd_out)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		if (fd_out > 0)
		{
			ft_putstr_fd(path, fd_out);
			write(fd_out, "\n", 1);
		}
		else if (k == 0)
		{
			ft_putstr_fd(path, fd);
			write(fd, "\n", 1);
		}
		else
		{
			ft_putstr_fd(path, 1);
			write(1, "\n", 1);
		}
	}
	else
		perror("getcwd() error");
}

void	put_str(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i++;
		else
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}