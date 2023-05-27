/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exutcutin_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:24:11 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/25 18:58:05 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_clr()
{
    printf("\n");
    if (sig->signal == 0)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
		sig->status = 1;
	}
}

void	open_infile(char *s,t_minishell *lst)
{
	
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

void	open_append(char *s, t_minishell *lst)
{
	lst->out_id = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (lst->out_id == -1)
		perror(s);
} 

void	check_erorrs(char *s)
{
	if (ft_isalpha(s[0]) == 0)
	{
		printf("export : %s not a valid identifier\n", s);
		exit(1);
	}
}