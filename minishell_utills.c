/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utills.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:11:29 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/07 20:21:15 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


void    __built__in__(t_env *lst,int ac ,char **av)
{
    char *buff;
 
	while (ac && av)
	{
		buff = readline("afadlane$ > ");
		if(buff == NULL) 
			exit(1);
		if (buff[0] == '\0')
		{
			free(buff);
			continue;
		}
		add_history(buff);
        __built__(lst,buff);
		// else
		// 	__pipex__(lst,buff);  
		free(buff);
	}
}