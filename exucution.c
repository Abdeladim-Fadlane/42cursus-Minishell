/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exucution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:50:00 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/24 16:18:47 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(t_env *p)
{
	int		i;
	int		k;
	char	**ptr;

	i = 0;
	k = ft_lstsize(p);
	ptr = malloc(sizeof(char *) * (k + 1));
	while (p && i < k)
	{
		ptr[i] = ft_strjoin(p->key, ft_strjoin("=", p->data));
		i++;
		p = p->next;
	}
	ptr[i] = NULL;
	return (ptr);
}

void	exitstatus(void)
{
	int	h;

	while (waitpid(-1, &h, 0) != -1)
	{
		WEXITSTATUS(h);
		sig->status = h;
		if(WIFSIGNALED(h))
		{
			if(WTERMSIG(h) == 3)
			{
				write(1,"Quit: 3\n",9);
				sig->status = 131;
			}
			if(WTERMSIG(h) == 2)
			 	sig->status = 130;
		}
	}
}

void	error(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	write(2, "afadlane$: ", 11);
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	write(2, ": command not found", 19);
	write(2, "\n", 1);
	exit(127);
}

char	*get_cmd(char **ptr, char *lst, t_env *p)
{
	int		l;
	int		i;
	char	*buff;

	i = 0;
	l = 0;
	buff = "";
	if (access(lst, F_OK) == 0)
		return (lst);
	if (check_env(p) == NULL)
	{
		write(2, lst, ft_strlen(lst));
		write(2, ": No such file or directory\n", 28);
		exit(127);
	}
	while (ptr[i])
	{
		buff = ft_strjoin(ptr[i], "/");
		buff = ft_strjoin(buff, lst);
		if (access(buff, F_OK) == 0)
			return (buff);
		free(buff);
		i++;
	}
	return (NULL);
}

char	*check_env(t_env *p)
{
	while (p->next)
	{
		if (ft_strcmp(p->next->key, "PATH") == 0)
			return (p->next->data);
		p = p->next;
	}
	return (NULL);
}
