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

void	ft_print(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		printf("str = %s\n", s[i]);
		i++;
	}
	printf("last str = %s\n", s[i]);
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

void	__readline__(t_env *lst)
{
	char *buff;
	char *line;
	char **arg;
	t_minishell *shell;
	shell = 0;
		
	signal(SIGINT, handle_clr);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{	
		sig->signal = 0;
		buff = readline("afadlane$> ");
		if (!buff)
		{
			write(2, "exit\n", 5);
			sig->status = 0;
			exit(0);
		}
		if (buff[0] == '\0')
		{
			free(buff);
			continue ;
		}
		line = malloc((ft_strlen(buff) + 1) + (all_redric(buff) * 2)); // This is the way!!
		detach_rediec(buff, line);
		if (check_syntext(line) != 404 && line[0])
		{
			arg = ft_split_parse(line, '|');
			shell = parsing(arg, lst);
			__main__(lst, shell);
		}
		else
		{
			perror("Syntext Error");
			exit(1);
		}
		add_history(buff);
		free(buff);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env *lst = NULL;
	char **p;
	int j;
	(void)ac;
	(void)av;
	sig = malloc(sizeof(t_sig));

	//shell = 0;
	j = -1;
	lst = 0;
	while (++j < len_env(env))
	{
		p = array_env(env, j);
		ft_add_back_env(&lst, ft_lstnew_env(p[0], p[1]));
		free(p);
	}
	// j = 0;
	// while (env[j])
	// {
	// 	p = __split__(env, j);
	// 	ft_lstadd_back(&lst, ft_lstnew(p[0], p[1]));
	// 	free(p);
	// 	j++;
	// }
	ft_lstadd_back(&lst, ft_lstnew("OLDPWD", NULL));
	__readline__(lst);
	// This is the way!!
}
