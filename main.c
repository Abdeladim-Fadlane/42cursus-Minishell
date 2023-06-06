/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:15 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/06 17:02:55 by ayylaaba         ###   ########.fr       */
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
	t_redir		*new;

	p = list;
	obj = NULL;
	while (list)
	{
		while (list->redirct)
		{
			if (list->redirct->type == INF)
			{
				open_infile(list->redirct->in, list);
				free(list->redirct->in);
			}
			if (list->redirct->type == OUT)
			{
				open_outfile(list->redirct->out, list);
				free(list->redirct->out);	
			}
			if (list->redirct->type == APE)
				open_append(list->redirct->out, list);
			if (list->redirct->type == DEL)
			{
				t_lstadd_back(&obj, t_lstnew(list->redirct->limiter));
				lst->n = 1;
				free(list->redirct->limiter);
			}
			new = list->redirct;
			list->redirct = list->redirct->next;
			free (list->redirct);
		}
		list = list->next;
	}
	pipex(p, lst, obj);

}

int	trim_pipex(t_minishell *lst, t_env *p)
{
	int pid;

	pipe(p->fd);
	first_proccess(p,lst->all_cmds, lst);
	p->flag_fd = p->fd[0];
	close(p->fd[1]);
	lst = lst->next;
	while (2 <= lstsize(lst))
	{
		if (lst->pipe == 1)
		{
			pipe(p->fd);
			midlle_proccess(p, lst->all_cmds, lst);
			close(p->fd[1]);
			close(p->flag_fd);
			p->flag_fd = p->fd[0];
		}
		lst = lst->next;
	}
	pid = last_proccess(p, lst->all_cmds, lst);
	close(p->flag_fd);
	return (pid);
}

void	pipex(t_minishell *lst, t_env *p, t_object *obj)
{
	g_sig->flag = 0;
	if (p->n >= 1)
	{
		main_herdoc(p, obj);
		if (!lst->all_cmds[0])
			return ;
	}
	if (lstsize(lst) == 1)
		one_command(lst->all_cmds, lst, p);
	else
		exitstatus(trim_pipex(lst, p));
}
