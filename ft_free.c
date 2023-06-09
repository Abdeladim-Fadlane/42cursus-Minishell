/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:28:53 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/09 11:34:05 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_data(t_minishell *shell)
// {
// 	int	i;

// 	i = 0;
// 	while (shell)
// 	{
// 		i = 0;
// 		printf("index : %d      pipe : %d\n", shell->index, shell->pipe);
// 		while (shell->all_cmds[i])
// 		{
// 			printf("cmd[%d] == %s\n", i, shell->all_cmds[i]);
// 			i++;
// 		}
// 		while (shell->redirct)
// 		{
// 			if (shell->redirct->type == INF)
// 				printf("INFILE : %s\n", shell->redirct->in);
// 			if (shell->redirct->type == OUT)
// 				printf("OUTFILE : %s\n", shell->redirct->out);
// 			shell->redirct = shell->redirct->next;
// 		}
// 		shell = shell->next;
// 	}
// }

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