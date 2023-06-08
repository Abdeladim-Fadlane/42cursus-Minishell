/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:15 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/08 19:52:38 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strim_her_doc(char *s, char *buff)
{
	if (buff == NULL)
	{
		free(buff);
		exit(0);
	}
	if (ft_strcmp(s, buff) == 0)
		exit(0);
}

int		check_delmiter(char	*h)
{
	int		i;
	char 	*str;

	str = ft_strtrim(h, " ");
	i = 0;
	if ((str[0] == '\"' && str[strlen(h) - 1] == '\"') || (str[0] == '\'' && str[strlen(h) - 1] == '\''))
		return 1;
	return 0;
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
			strim_her_doc(s, buff);
			if (buff[0] == '\0')
			{
				free(buff);
				continue ;
			}
			ft_putstr_fd(buff, p->fd2[1]);
			ft_putstr_fd("\n", p->fd2[1]);
		}
	}
	close(p->fd2[1]);
	wait(NULL);
	g_sig->signal = 0;
}

void	__main__(t_env *lst, t_minishell *list)
{
	t_minishell	*p;
	t_object	*obj;
	
	p = list;
	obj = NULL;
	while (list)
	{
		list->out_id = -1;
		while (list->redirct)
		{
			if (list->redirct->type == INF)
			{
				if(open_infile(list->redirct->in, list) == 1)
					return;
				free(list->redirct->in);
			}
			if (list->redirct->type == OUT)
			{
				if(open_outfile(list->redirct->out, list) == 1)
					return;
				free(list->redirct->out);
			}
			if (list->redirct->type == APE)
				if(open_append(list->redirct->out, list) == 1)
					return;
			if (list->redirct->type == DEL)
			{
				t_lstadd_back(&obj, t_lstnew(list->redirct->limiter));
				lst->n = 1;
			}
			list->redirct = list->redirct->next;
		}
		list = list->next;
	}
	pipex(p, lst, obj);
}
