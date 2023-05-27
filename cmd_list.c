/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:22:14 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/05/14 14:08:53 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char *str)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->cmd = str;
	cmd->next = 0;
	return (cmd);
}

t_cmd	*ft_last_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	add_back_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tem;

	if (!*cmd)
		*cmd = new;
	else
	{
		tem = ft_last_cmd(*cmd);
		tem->next = new;
	}
}

int	count_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

char	**pass_cmds(t_cmd *cmd)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof(char *)*(count_cmd(cmd) + 1));
	if (!cmds)
		return 0;
	while (cmd)
	{
		cmds[i++] = cmd->cmd;
		cmd = cmd->next;
	}
	cmds[i] = NULL;
    return (cmds);
}
