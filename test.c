/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:49:23 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/29 21:49:28 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	print_data(t_minishell *shell)
// {
// 	int i;

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
// 			if (shell->redirct->type == APE)
// 				printf("APPEND : %s\n", shell->redirct->out);
// 			if (shell->redirct->type == DEL)
// 				printf("DELIMITER : %s \n", shell->redirct->limiter);
// 			shell->redirct = shell->redirct->next;
// 		}
// 		shell = shell->next;
// 	}
// }

// void	ft_print(char **s)
// {
// 	int i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		printf("str = %s\n", s[i]);
// 		i++;
// 	}
// 	printf("last str = %s\n", s[i]);
// }