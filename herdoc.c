/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:03:36 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/09 12:14:02 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	max_delmi(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
			count++;
		i++;
	}
	if (count > 16)
		return (1);
	return (0);
}

void	__her_doc(char *s, char *buff)
{
	if (buff == NULL)
	{
		free(buff);
		exit(0);
	}
	if (ft_strcmp(s, buff) == 0)
	{
		free(buff);
		free(s);
		exit(0);
	}
}

void	her_doc(char *s, t_env *p)
{
	int		pid;
	char	*buff;

	g_sig->signal = 1;
	pipe(p->fd2);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			buff = readline(">");
			if (g_sig->dude == 1)
				buff = expand(buff, ft_strdup(""), p, 0);
			__her_doc(s, buff);
			ft_putstr_fd(buff, p->fd2[1]);
			ft_putstr_fd("\n", p->fd2[1]);
			free(buff);
		}
	}
	close(p->fd2[1]);
	wait(NULL);
	g_sig->signal = 0;
}

void	main_herdoc(t_env *p, t_object *obj)
{
	while (obj)
	{
		her_doc(obj->s, p);
		obj = obj->next;
	}
}
