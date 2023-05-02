/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:23 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/02 14:03:40 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


void	print_export(t_env *p);
void	ft_pwd(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
		perror("getcwd() error");
}

void	ft_echo(char *s,char *op)
{

	write(1, s, ft_strlen(s));
	if(op)
		write(1, "\n", 2);
}

void	get_index_pwd(t_env *lst, char *path)
{
	int		i;
	t_env	*p;

	p = lst;
	i = 0;

	while (p->next)
	{
		if (ft_strcmp(p->key, "PWD") == 0)
			p->data = ft_strdup(path);
		// if (ft_strcmp(p->data, "OLDPWD") == 0)
		// 	p->key = path;
		p = p->next;
	}
}

void	ft_cd(char *str, t_env *p)
{
	char	path[1024];
	char	*buff;
	char	*t;

	buff = getcwd(path, sizeof(path));
	t = ft_strjoin(buff, ft_strjoin("/", str));
	if (chdir(t) != 0)
		perror("cd ");
	buff = getcwd(path, sizeof(path));
	get_index_pwd(p, buff);
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

void	print_env(t_env *p)
{
	while (p)
	{
		if(p->data != NULL)
		{
			printf("%s", p->key);
			printf("=");
			printf(" \"%s\" \n", p->data);
		}
		p = p->next;
	}
}

void	print_export(t_env *p)
{
	while (p)
	{
		printf("declare -x ");
		printf("%s", p->key);
		if(p->data != NULL)
		{
			printf("=");
			printf(" \"%s\" \n", p->data);
		}
		else
			printf("\n");	
		p = p->next;
	}
}

void    ft_readline(t_env *lst,int ac ,char **av)
{
    char *buff;
 
	while (ac && av)
	{
		buff = readline("afadlane$ > ");
		if(buff == NULL) 
			exit(1);
		if (buff[0] == '\0')
		{
			free(buff);
			continue;
		}
		
		add_history(buff);
		if (ft_strcmp(buff, "pwd") == 0)
			ft_pwd();
		if (ft_strcmp(buff, "cd") == 0)
			ft_cd("bonus", lst);
		if (ft_strcmp(ft_split(buff ,' ')[0], "echo") == 0)
			ft_echo(ft_split(buff ,' ')[1],"-n");
		if (ft_strcmp(buff, "env") == 0)
			print_env(lst);
		if (ft_strcmp(ft_split(buff,' ')[0], "export") == 0)
		{  
			_add_to_export(lst,buff);
			if(ft_split(buff,' ')[1] == NULL)
				print_export(lst);
		}
		if (ft_strcmp(buff, "exit") == 0)
		{
			printf("exit\n");
			exit(0);
		}
		free(buff);
	}
}