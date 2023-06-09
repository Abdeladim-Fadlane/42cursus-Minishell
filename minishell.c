/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/04/18 13:14:03 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 13:14:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_data(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell)
	{
		i = 0;
		printf("index : %d      pipe : %d\n", shell->index, shell->pipe);
		while (shell->all_cmds[i])
		{
			printf("cmd[%d] == %s\n", i, shell->all_cmds[i]);
			i++;
		}
		while (shell->redirct)
		{
			if (shell->redirct->type == INF)
				printf("INFILE : %s\n", shell->redirct->in);
			if (shell->redirct->type == OUT)
				printf("OUTFILE : %s\n", shell->redirct->out);
			shell->redirct = shell->redirct->next;
		}
		shell = shell->next;
	}
}

void	ft_free_redir(t_minishell *shell)
{
	t_redir		*org;

	while (shell->redirct)
	{
		if (shell->redirct->type == 1 || shell->redirct->type == 4)
			free(shell->redirct->out);
		if (shell->redirct->type == 2)
			free(shell->redirct->in);
		if (shell->redirct->type == 3)
			free(shell->redirct->limiter);
		org = shell->redirct;
		shell->redirct = shell->redirct->next;
		free(org);
	}
}

void	ft_globle_free(t_minishell *shell)
{
	t_cmd		*org;
	t_minishell	*org1;

	while (shell)
	{
		free(shell->all_cmds);
		free(shell->s1);
		ft_free_redir(shell);
		while (shell->cmd)
		{
			free(shell->cmd->cmd);
			org = shell->cmd;
			shell->cmd = shell->cmd->next;
			free(org);
		}
		org1 = shell;
		shell = shell->next;
		free(org1);
	}
}

int	addoldpwd(t_env *lst, int ac, char **av)
{
	(void)ac;
	(void)av;
	while (lst)
	{
		if (ft_strcmp(lst->key, "OLDPWD") == 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

char	**parse_to_part(char *line)
{
	char **s;
	char *ptr;
	int i;

	s = ft_split_parse(line, '|');
	i = 0;
	while (s[i])
	{
		ptr = s[i];
		s[i] = ft_strtrim(s[i], " ");
		free(ptr);
		i++;
	}
	return (s);
}

int		max_delmi(char *s)
{
	int		i;
	int		count;

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

void	ft_print(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf ("str == %s\n", s[i]);
		i++;
	}
	printf ("str == %s\n", s[i]);
}

void	norm_readline(t_env *lst, t_minishell *shell, char *buff)
{
	char **arg;
	char *line;

	arg = 0;
	line = 0;
	//(void)lst;
	if (check_syntext(buff) != 404 && buff[0])
	{
		line = malloc((ft_strlen(buff) + 1) + (all_redric(buff, 0, 0) * 2));
		detach_rediec(buff, line, 0, 0);
		if (max_delmi(line) == 1)
		{
			write(2, "maximum here-document count exceeded\n", 37);
			exit (2);
		}
		arg = ft_split_parse(line, '|');
		shell = parsing(arg, lst);
		print_data(shell);
		__main__(lst, shell);
	}
	else
	{
		g_sig->status = 256;
		perror("Syntext Error");
	}
	add_history(buff);
	free(buff);
	free(arg);
	ft_globle_free(shell);
}

int		check_space(char *s)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			count++;
		i++;
	}
	if (count == ft_strlen(s))
		return (1);
	return (0);
}

void	__readline__(t_env *lst)
{
	char *buff;
	t_minishell *shell;

	shell = 0;
	g_sig->status = 0;
	signal(SIGINT, handle_clr);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_sig->signal = 0;
		buff = readline("afadlane$> ");
		if (!buff)
		{
			write(2, "exit\n", 5);
			exit(0);
		}
		if (buff[0] == '\0' || check_space(buff) == 1)
		{
			free(buff);
			continue ;
		}
		norm_readline(lst, shell, buff);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env *lst;
	char **p;
	int j;

	g_sig = malloc(sizeof(t_sig));
	g_sig->flag =0;
	j = -1;
	lst = NULL;
	char *s = ft_strdup ("OLDPWD");
	while (++j < len_env(env))
	{
		p = array_env(env, j);
		if (ft_strcmp(p[0], s) == 0)
		{
			free(p[1]);
			p[1] = NULL;
		}
		ft_add_back_env(&lst, ft_lstnew_env(p[0], p[1]));
		ft_free(p);
	}
	if (addoldpwd(lst, ac, av))
		ft_lstadd_back(&lst, ft_lstnew(s, NULL));
	free(s);
	__readline__(lst);
}
