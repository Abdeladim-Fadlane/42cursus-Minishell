/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fille.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:45:43 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/09 11:39:54 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_clr(int n)
{
	n = 0;
	printf("\n");
	if (g_sig->signal == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig->status = 1;
	}
}

int	open_infile(char *s, t_minishell *lst)
{
	lst->in_id = open(s, O_RDONLY, 0644);
	if (lst->in_id == -1)
	{
		perror(s);
		return(1);
	}
	return(0);
}

int	open_outfile(char *s, t_minishell *lst)
{

	lst->out_id = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (lst->out_id == -1)
	{
		perror(s);
		return(1);
	}
	return(0);
}

int	open_append(char *s, t_minishell *lst)
{
	lst->out_id = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (lst->out_id == -1)
	{
		perror(s);
		return(1);
	}
	return(0);
}