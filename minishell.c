/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:23 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/07 20:44:56 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


void	__print__export__(t_env *p);
void	__pwd__(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
		perror("getcwd() error");
}

void	__echo__(char *s)
{
	int i = 1;
	char **p = ft_split(s,' ');
	if(p[1] == NULL)
	{
		write(1, "\n", 2);
		return;
	}
	if(ft_strcmp(p[1],"-n") == 0 && p[2] == NULL)
		return ;
	else
	{
		while(ft_strcmp(p[i],"-n") == 0)
			i++;
		while(p[i])
		{
			write(1, p[i], ft_strlen(p[i]));
			if(p[i+1] != NULL)
				write(1, " ", 2);
			i++;
		}		
	}
	if(ft_strcmp(p[1],"-n") != 0)
		write(1, "\n", 2);
}

void	get_index_pwd(t_env *lst, char *path,char *s)
{
	int		i;
	t_env	*p;

	p = lst;
	i = 0;

	while (p->next)
	{		
		if (ft_strcmp(p->key, "OLDPWD") == 0)
			p->data = ft_strdup(s);
		else if (ft_strcmp(p->key, "PWD") == 0)
			p->data = ft_strdup(path);
		p = p->next;
	}
	
}
char	*get_user(t_env *lst)
{
	while(lst)
	{
		if(ft_strcmp(lst->key,"USER") == 0)
			return(lst->data);
		lst = lst->next;
	}
	return NULL;
}
void	__cd__(char *str, t_env *p)
{
	char	path[1024];
	char	pathh[1024];
	char	*buff;
	char	*t;
	char *s = getcwd(pathh, sizeof(pathh));
	if(!str)
	{
		if (chdir(ft_strjoin("/Users/", ft_strjoin("/", get_user(p)))) != 0)
			perror("cd ");
		get_index_pwd(p, getcwd(path, sizeof(path)),s);
	}
	else	
	{
		buff = getcwd(path, sizeof(path));
		t = ft_strjoin(buff, ft_strjoin("/", str));
		if (chdir(t) != 0)
			perror("cd ");
		get_index_pwd(p,getcwd(path, sizeof(path)) ,s);

		
	}
}

char	**split_pwd(char **env, int j)
{
	char	**p;
	int		i;
	int		k;
	int		len;

	len = 0;
	i = 0;
	k = 0;
	p = malloc(sizeof(char *) * 3 + 1);
	while (env[j][i] != '=')
		i++;
	while (env[j][len])
		len++;
	p[0] = ft_substr(env[j], 0, i);
	p[1] = ft_substr(env[j], i + 1, len);
	p[2] = 0;
	return (p);
}

int	get_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return i;
}

void	__print__env__(t_env *p)
{
	while (p)
	{
		if(p->data != NULL)
		{
			printf("%s", p->key);
			printf("=");
			printf("\"%s\" \n", p->data);
		}
		p = p->next;
	}
}

void	__print__export__(t_env *p)
{
	while (p)
	{
		printf("declare -x ");
		printf("%s", p->key);
		if(p->data != NULL)
		{
			printf("=");
			printf("\"%s\" \n", p->data);
		}
		else
			printf("\n");	
		p = p->next;
	}
}

void	__unset__(t_env *lst,char *s)
{
	char **p = ft_split(s,' ');
	int i = 1;
	t_env *tmp;
	
	while(lst->next)
	{
		while(p[i])
		{
			if(ft_strcmp(lst->next->key,p[i]) == 0 )
			{
				tmp = lst->next->next;
				free(lst->next);
				lst->next = tmp;	
			}
			if( lst->next == NULL)
				return ;
			i++;
		}
		i = 1;
		lst = lst->next;
	}
	
}

void    __built__(t_env *lst ,char *buff)
{
    	if (ft_strcmp(buff, "pwd") == 0)
			__pwd__();
		if (ft_strcmp(ft_split(buff ,' ')[0], "cd") == 0)
			__cd__(ft_split(buff ,' ')[1], lst);
		if (ft_strcmp(ft_split(buff ,' ')[0], "echo") == 0)
			__echo__(buff);
		if (ft_strcmp(buff, "env") == 0)
			__print__env__(lst);
		if (ft_strcmp(ft_split(buff,' ')[0], "export") == 0)
		{  
			__add__to__export__(lst,buff);
			if(ft_split(buff,' ')[1] == NULL)
				__print__export__(lst);
		}
		if (ft_strcmp(buff, "exit") == 0)
		{
			printf("exit\n");
			exit(0);
		}
		if (ft_strcmp(ft_split(buff,' ')[0], "unset") == 0)
		{
			if(ft_split(buff,' ')[1] == NULL)
				exit(0);
			else
				__unset__(lst,buff);
		}
}

