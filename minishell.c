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

void	open_infile(char *s,t_minishell *lst)
{
	//printf("%s-----\n", lst->redirct->in);
	lst->in_id = open(s, O_RDONLY, 0644);
	if (lst->in_id == -1)
	{
		perror(s);
		exit(1);
	}
}

void	open_outfile(char *s,t_minishell *lst)
{
	lst->out_id = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (lst->out_id == -1)
		perror(s);
} 

void	her_doc(char *s,t_minishell *lst)
{
	(void)lst;
	while (1)
	{
		char *buff = readline(">");
		if (buff == NULL)
		{
			free(buff);
			break;
		}
		if (buff[0] == '\0')
		{
			free(buff);
			continue ;
		}
		if(ft_strcmp(s,buff) == 0)
		{
			break;
			exit(0);
		}
	}
	
}

void	print_data(t_minishell *shell)
{
	int i;

	while (shell)
	{
		i = 0;
		//printf("index : %d      pipe : %d\n", shell->index, shell->pipe);
		while (shell->redirct)
		{
			if (shell->redirct->type == INF)
			{
				
				open_infile(shell->redirct->in,shell);
				
			}
			if (shell->redirct->type == OUT)
				open_outfile (shell->redirct->out,shell);
			if (shell->redirct->type == APE)
				printf("APPEND : %s\n", shell->redirct->out);
			if (shell->redirct->type == DEL)
				her_doc(shell->redirct->limiter,shell);
			shell->redirct = shell->redirct->next;
		}
		shell = shell->next;
	}
}

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
	t_minishell *shell;
	shell = malloc(sizeof(t_minishell));
	while (ac && av)
	{
		buff = readline("afadlane$ > ");
		if (buff == NULL)
			exit(1);
		if (buff[0] == '\0')
		{
			free(buff);
			continue ;
		}
		line = malloc(sizeof(char) * ft_strlen(buff) + (all_redric(buff) * 2) + 1); // zay l3assl yassmina
		line = detach_rediec(buff, line); 
		arg = parse_to_part(line); 
		if (check_syntext(line) != 404 && line[0])
		{
			shell = parsing(arg);
			__main__(lst, env,shell,buff);
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

