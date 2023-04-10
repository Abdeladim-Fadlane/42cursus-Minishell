/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:15 by afadlane          #+#    #+#             */
/*   Updated: 2023/04/10 02:00:49 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
		perror("getcwd() error");
}

void	ft_echo(char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 2);
}

void	ft_cd(char *str, t_lst *p)
{
	char	path[1024];
	char	*buff;
	char	*t;

	buff = getcwd(path, sizeof(path));
	t = ft_strjoin(buff, ft_strjoin("/", str));
	if (chdir(t) != 0)
		perror("cd ");
	p->data = ft_strjoin("PWD=",t);
	//execve("/bin/pwd", arg, env);
}

t_lst	*change_pwd(t_lst *lst)
{
	int		i;
	t_lst	*p;

	p = lst;
	i = 0;
	while (p)
	{
		if (ft_strnstr(p->data, "PWD=", 4) != NULL)
			return (p);
		p = p->next;
	}
	return (p);
}

void	creat_linkedlist(t_lst *lst, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
		i++;
	j = 0;
	while (j < i)
	{
		lst->data = env[j];
		lst->next = malloc(sizeof(t_lst));
		lst->next->prev = lst;
		lst = lst->next;
		j++;
	}
}

void	print_env(t_lst *p)
{
	while(p->next)
	{
		printf("%s\n",p->data);
		p = p->next;
	}
}

int	main(int ac, char **av, char **env)
{
	//char *bufff;
	//char *arg[] = {"pwd", NULL};
	(void)ac;
	(void)av;

	t_lst *lst = malloc(sizeof(t_lst));
	creat_linkedlist(lst, env);
	t_lst *tmp = change_pwd(lst);
	//tmp->data = "ewf";
	ft_cd("bonus", tmp);
	print_env(lst);
	//env[check_env(env)] = "PWD=/User/afadlane/Desktop/Minishell/bonus";
	//char *pwd = malloc(ft_strlen(t) + 1);
	// int u = 0;
	// while (env[u])
	// 	u++;
	// for (int y = 0; y < u; y++)
	// {
	// 	printf("%s\n", env[y]);
	// }
	// while (ac && av)
	// {
	// 	bufff = readline("Minishell >");
	// 	add_history(bufff);
	// 	if (bufff == NULL)
	// 		break ;
	// 	if (strncmp(bufff, "pwd", 3) == 0)
	// 		ft_pwd();
	// 	if (strncmp(bufff, "cd", 2) == 0)
	// 		ft_cd("bonus");
	// 	if (strncmp(bufff, "echo", 3) == 0)
	// 		ft_echo(bufff);
	// 	free(bufff);
	// 	bufff = readline("Minishell >");
	// }
}