/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/0rr  5z/14 16:00:49 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/15 14:53:44 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h" 

void	__cd__(char *str, t_env *p)
{
	char	path[1024];
	char	pathh[1024];
	char	*buff;
	char	*t;
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
		t = ft_strjoin(buff, ft_strjoin("/", str));
		if (chdir(t) != 0)
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

void	__print__env__(t_env *p,int k,int fd,int fdd)
{
	while (p)
	{
		if (p->data != NULL)
		{
			if(fdd > 0)
			{
				ft_putstr_fd(p->key,fdd);
				ft_putstr_fd("=",fdd);
				ft_putstr_fd(p->data,fdd);
				write(fdd,"\n", 1);
			}
			else if(k == 0)
			{
				ft_putstr_fd(p->key,fd);
				ft_putstr_fd("=",fd);
				ft_putstr_fd(p->data,fd);
				write(fd,"\n", 1);
			}
			else
			{
				printf("%s", p->key);
				printf("=");
				printf("%s\n", p->data);
			}
		}
		p = p->next;
	}
}

void	__print__export__(t_env *p,int k ,int fd,int fdd)
{
	while (p)
	{
		if(fdd>0)
		{
			ft_putstr_fd("declare -x ",fdd);
			ft_putstr_fd( p->key,fdd);
			if (p->data != NULL)
			{
				ft_putstr_fd("=\"",fdd);
				ft_putstr_fd(p->data, fdd);
				ft_putstr_fd("\"\n", fdd);
			}
			else
				printf("\n");

		}
		else if(k == 0)
		{
			ft_putstr_fd("declare -x ",fd);
			ft_putstr_fd( p->key,fd);
			if (p->data != NULL)
			{
				ft_putstr_fd("=\"",fd);
				ft_putstr_fd(p->data, fd);
				ft_putstr_fd("\"\n", fd);
			}
			else
				printf("\n");
		}
		else
		{
			printf("declare -x %s",p->key);
			if (p->data != NULL)
			{
				printf("=");
				printf("\"%s\"\n", p->data);
			}
			else
				printf("\n");
		}
		p = p->next;
	}
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