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

void	error_max_deli(void)
{
	write(2, "maximum here-document count exceeded\n", 37);
	exit(2);
}

void	norm_readline(t_env *lst, t_minishell *shell, char *buff)
{
	char	**arg;
	char	*line;

	arg = 0;
	line = 0;
	if (check_syntext(buff) != 404 && buff[0])
	{
		line = malloc((ft_strlen(buff) + 1) + (all_redric(buff, 0, 0) * 2));
		detach_rediec(buff, line, 0, 0);
		if (max_delmi(line) == 1)
			error_max_deli();
		arg = ft_split_parse(line, '|');
		shell = parsing(arg, lst);
		__main__(lst, shell);
	}
	else
	{
		g_sig->status = 256;
		perror("Syntext Error");
	}
	free(buff);
	free(arg);
	ft_globle_free(shell);
}

void	__readline__(t_env *lst)
{
	char		*buff;
	t_minishell	*shell;

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
		if (buff[0] == '\0')
		{
			free(buff);
			continue ;
		}
		add_history(buff);
		norm_readline(lst, shell, buff);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*lst;
	char	**p;
	int		j;
	char	*s;

	g_sig = malloc(sizeof(t_sig));
	g_sig->flag = 0;
	j = -1;
	lst = NULL;
	s = ft_strdup("OLDPWD");
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
