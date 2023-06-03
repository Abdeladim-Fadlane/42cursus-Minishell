/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:16:24 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/30 16:24:02 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(char *s)
{
	int	j;

	j = 2;
	if (s[0] == '-' && s[1] == 'n')
	{
		if (ft_strcmp(s, "-n") == 0)
			return (0);
		while (s[j])
		{
			if (s[j] != 'n')
				return (1);
			j++;
		}
		return (0);
	}
	return (1);
}

int	ft_norm(t_minishell *lst)
{
	int	i;

	i = 1;
	while (lst->all_cmds[i])
	{
		if (check_option(lst->all_cmds[i]) == 0)
			i++;
		else
			break ;
	}
	return (i);
}

void	norm_echo(t_minishell *lst, int k, int fd, int fdd)
{
	int	i;

	i = ft_norm(lst);
	while (lst->all_cmds[i])
	{
		if (fdd > 0)
		{
			put_str(lst->all_cmds[i], fdd);
			if (lst->all_cmds[i + 1] != NULL)
				write(fdd, " ", 2);
		}
		else if (k == 0)
		{
			put_str(lst->all_cmds[i], fd);
			if (lst->all_cmds[i + 1] != NULL)
				write(fd, " ", 2);
		}
		else
		{
			put_str(lst->all_cmds[i], 1);
			if (lst->all_cmds[i + 1] != NULL)
				write(1, " ", 2);
		}
		i++;
	}
}

void	print_echo(t_minishell *lst, int k, int fd, int fdd)
{
	if (fdd > 0)
	{
		if (check_option(lst->all_cmds[1]) != 0)
			write(fdd, "\n", 1);
	}
	else if (k == 0)
	{
		if (check_option(lst->all_cmds[1]) != 0)
			write(fd, "\n", 1);
	}
	else
	{
		if (check_option(lst->all_cmds[1]) != 0)
			write(1, "\n", 1);
	}
}

void	__echo__(t_minishell *lst, int k, int fd, int fdd)
{
	if (lst->all_cmds[1] == NULL)
	{
		if (fdd > 0)
			write(fdd, "\n", 1);
		if (k == 0)
			write(fd, "\n", 1);
		else
			write(1, "\n", 1);
		return ;
	}
	norm_echo(lst, k, fd, fdd);
	print_echo(lst, k, fd, fdd);
}
