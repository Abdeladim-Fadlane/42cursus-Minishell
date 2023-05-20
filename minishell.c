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



// void	print_data(t_minishell *shell)
// {
// 	while (shell)
// 	{
// 		while (shell->redirct)
// 		{
// 			if (shell->redirct->type == INF)
// 				open_infile(shell->redirct->in,shell);
// 			if (shell->redirct->type == OUT)
// 				open_outfile (shell->redirct->out,shell);
// 			if (shell->redirct->type == APE)
// 				open_append (shell->redirct->out,shell);
// 			if (shell->redirct->type == DEL)
// 			{
// 				her_doc(shell->redirct->limiter,shell);
// 			}
				
// 			shell->redirct = shell->redirct->next;
// 		}
// 		shell = shell->next;
// 	}
// }

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

char **get_env(t_env *p)
{
	int i = 0;
	int k = ft_lstsize(p);
	char **ptr = malloc(sizeof(char *) * (k + 1));
	while(p && i < k)
	{
		ptr[i] = ft_strjoin(p->key,ft_strjoin("=",p->data));
		i++;
		p = p->next;
	}
	ptr[i] = NULL;
	return (ptr);
}

void    handle_clr(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
		s = 1;
	}
}

int	main(int ac, char **av, char **env)
{
	char *buff ;
	char *line ;
	char **arg;
	t_env *lst = NULL;
	// (void)ac;
	// (void)av;
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
	//ft_lstadd_back(&lst, ft_lstnew("OLDPWD", NULL));
	t_minishell *shell;
	shell = malloc(sizeof(t_minishell));
	while (ac && av)
	{
		signal(SIGINT, handle_clr);
		signal(SIGQUIT, SIG_IGN);
		buff = readline("afadlane$ > ");
		if (!buff)
		{
			write(2, "exit\n", 5);
			s = 0;
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
			__main__(lst, env,shell);
		}
		else if (!buff[0])
		{
			printf("Syntext Error\n");
			free(buff);
		}
		add_history(buff);
		free(buff);
	}
	return (0);
}

