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
	int	i;

	i = 0;
	while (s[i])
	{
		printf ("str = %s\n", s[i]);
		i++;
	}
	printf ("last str = %s\n", s[i]);
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

void    __readline__(t_env *lst)
{
	
	char *buff ;
	char *line ;
	char **arg;
	t_minishell *shell;
	shell = malloc(sizeof(t_minishell));
	while (1)
	{
		sig->signal = 0;
		signal(SIGINT, handle_clr);
		signal(SIGQUIT, SIG_IGN);
		buff = readline("afadlane$> ");
		if (!buff)
		{
			write(2, "exit\n", 5);
			sig->signal = 0;
			exit(0);
		}
		if (buff[0] == '\0')
		{
			free(buff);
			continue ;
		}
		line = malloc(sizeof(char) * ft_strlen(buff) + (all_redric(buff) * 2) + 1); // This is the way!!
		line = detach_rediec(buff, line); 
		arg = parse_to_part(line); 
		if (check_syntext(line) != 404 && line[0])
		{
			shell = parsing(arg);
			__main__(lst,shell);
		}
		add_history(buff);
		free(buff);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env *lst = NULL;
	(void)ac;
	(void)av;
	sig = malloc(sizeof(t_sig));
	char	**p;
	int		j;
	j = 0;
	
	while (env[j])
	{
		p = __split__(env, j);
		ft_lstadd_back(&lst, ft_lstnew(p[0], p[1]));
		free(p);
		j++;
	}
	ft_lstadd_back(&lst, ft_lstnew("OLDPWD", NULL));
	__readline__( lst);
	// This is the way!!
}

