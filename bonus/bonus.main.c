/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:36:51 by afadlane          #+#    #+#             */
/*   Updated: 2023/02/24 10:51:00 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*rasepath(char *p)
{
	while (*p != '/')
		p++;
	return (p);
}

int	check_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
			return (i);
		i++;
	}
	return (0);
}

void	pipex(t_object *lst, char **av, int ac)
{
	int		i;
	char	**buff;

	buff = ft_split(av[2], 32);
	if (pipe(lst->fd) < 0)
		ft_error();
	first_proccess(av, buff, lst);
	ft_free(buff);
	close(lst->fd[1]);
	lst->flag_fd = lst->fd[0];
	i = 3;
	while (ac - 2 > ++i)
	{
		if (pipe(lst->fd) < 0)
			ft_error();
		buff = ft_split(av[i], 32);
		if (i < ac - 2)
		{
			midlle_proccess(av, buff, lst, i);
			ft_free(buff);
		}
		close(lst->fd[1]);
		close(lst->flag_fd);
		lst->flag_fd = lst->fd[0];
	}
}

int	main(int ac, char **av, char **env)
{
	t_object	*lst;
	char		**buff;

	buff = ft_split(av[ac - 2], 32);
	lst = malloc(sizeof(t_object));
	lst->envp = env;
	if (check_env(lst->envp) == 0)
		ft_error1();
	lst->p = ft_split(rasepath(lst->envp[check_env(lst->envp)]), ':');
	if (ac > 4)
	{
		pipex(lst, av, ac);
		second_proccess(av, buff, lst, ac - 1);
		ft_free(buff);
		close(lst->flag_fd);
	}
	else
		ft_error();
	while (wait(NULL) != -1)
		;
}
