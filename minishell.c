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

void	norm_readline(t_env *lst, t_minishell *shell, char *buff)
{
	char **arg;
	char *line;

	line = malloc((ft_strlen(buff) + 1) + (all_redric(buff) * 2));
	detach_rediec(buff, line);
	if (check_syntext(line) != 404 && line[0])
	{
		arg = ft_split_parse(line, '|');
		shell = parsing(arg, lst);
		__main__(lst, shell);
	}
	else
	{
		g_sig->status = 256;
		perror("Syntext Error");
	}
	add_history(buff);
	free(line);
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
		if (buff[0] == '\0')
		{
			free(buff);
			continue ;
		}
		norm_readline(lst, shell, buff);
		free(buff);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env *lst;
	char **p;
	int j;

	g_sig = malloc(sizeof(t_sig)); //CHECK ENV AGMENT//
	j = -1;
	lst = NULL;
	while (++j < len_env(env))
	{
		p = array_env(env, j);
		if (ft_strcmp(p[0], "OLDPWD") == 0)
			p[1] = NULL;
		ft_add_back_env(&lst, ft_lstnew_env(p[0], p[1]));
		free(p);
	}
	if (addoldpwd(lst, ac, av))
		ft_lstadd_back(&lst, ft_lstnew("OLDPWD", NULL));
	__readline__(lst);
}
