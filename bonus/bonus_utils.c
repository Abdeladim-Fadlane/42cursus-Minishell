/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:14:33 by afadlane          #+#    #+#             */
/*   Updated: 2023/02/24 10:29:10 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

void	ft_error(void)
{
	write(2, "Error you put less than forth args !\n", 36);
	exit(1);
}

void	ft_error1(void)
{
	write(2, "command not found :\n", 20);
	exit(1);
}
