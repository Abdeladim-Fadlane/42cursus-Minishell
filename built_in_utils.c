/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:34:47 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/24 21:46:32 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strim_printenv(t_env *p, int fd)
{
	ft_putstr_fd(p->key, fd);
	ft_putstr_fd("=", fd);
	ft_putstr_fd(p->data, fd);
	write(fd, "\n", 1);
}

void	__print__env__(t_env *p, int k, int fd, int fdd)
{
	while (p)
	{
		if (p->data != NULL)
		{
			if (fdd > 0)
			{
				ft_putstr_fd(p->key, fdd);
				ft_putstr_fd("=", fdd);
				ft_putstr_fd(p->data, fdd);
				write(fdd, "\n", 1);
			}
			else if (k == 0)
				strim_printenv(p, fd);
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

void	trim_printexport(t_env *p, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(p->key, fd);
	if (p->data != NULL)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(p->data, fd);
		ft_putstr_fd("\"\n", fd);
	}
	else
		ft_putstr_fd("\n", fd);
}

void	trim1_printexport(t_env *p, int fdd)
{
	ft_putstr_fd("declare -x ", fdd);
	ft_putstr_fd(p->key, fdd);
	if (p->data != NULL)
	{
		ft_putstr_fd("=\"", fdd);
		ft_putstr_fd(p->data, fdd);
		ft_putstr_fd("\"\n", fdd);
	}
	else
		ft_putstr_fd("\n", fdd);
}

void	__print__export__(t_env *p, int k, int fd, int fdd)
{
	while (p)
	{
		if (fdd > 0)
			trim1_printexport(p, fdd);
		else if (k == 0)
			trim_printexport(p, fd);
		else
		{
			printf("declare -x %s", p->key);
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
