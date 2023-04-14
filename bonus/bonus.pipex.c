/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:36:31 by afadlane          #+#    #+#             */
/*   Updated: 2023/02/24 11:10:53 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *s)
{
	int	i;

	i = 0;
	write(2, "command not found : ", 21);
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	write(2, "\n", 1);
	exit(0);
}

char	*get_cmd(char **ptr, char **p)
{
	int		l;
	int		i;
	char	*buff;

	i = 0;
	l = 0;
	buff = "";
	if (access(ptr[0], F_OK) == 0)
		return (ptr[0]);
	while (p[l])
		l++;
	while (i < l)
	{
		buff = ft_strjoin(p[i], "/");
		buff = ft_strjoin(buff, ptr[0]);
		if (access(buff, F_OK) == 0)
			return (buff);
		i++;
	}
	return (NULL);
}

void	first_proccess(char **av, char **ptr, t_object *lst)
{
	int	fd1;

	lst->pid = fork();
	if (lst->pid == 0)
	{
		fd1 = open(av[1], O_RDONLY, 0644);
		if (fd1 == -1)
		{
			perror(av[1]);
			exit(1);
		}
		dup2(fd1, 0);
		close(lst->fd[0]);
		dup2(lst->fd[1], 1);
		if (get_cmd(ptr, lst->p) == NULL)
			error(av[2]);
		if (execve(get_cmd(ptr, lst->p), ptr, lst->envp) == -1)
			perror("execve : ");
	}
}

void	second_proccess(char **av, char **ptr2, t_object *lst, int k)
{
	int	fd2;

	lst->pid2 = fork();
	if (lst->pid2 == 0)
	{
		fd2 = open(av[k], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd2 == -1)
		{
			perror(av[k]);
			exit(1);
		}
		dup2(fd2, 1);
		dup2(lst->flag_fd, 0);
		if (get_cmd(ptr2, lst->p) == NULL)
			error(av[k - 1]);
		if (execve(get_cmd(ptr2, lst->p), ptr2, lst->envp) == -1)
			perror("execve : ");
	}
}

void	midlle_proccess(char **av, char **ptr2, t_object *lst, int k)
{
	lst->pid3 = fork();
	if (lst->pid3 == 0)
	{
		dup2(lst->flag_fd, 0);
		close(lst->fd[0]);
		if (get_cmd(ptr2, lst->p) == NULL)
			error(av[k]);
		dup2(lst->fd[1], 1);
		if (execve(get_cmd(ptr2, lst->p), ptr2, lst->envp) == -1)
			perror("execve : ");
	}
}
