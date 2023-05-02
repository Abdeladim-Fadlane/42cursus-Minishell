/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:15 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/02 20:17:08 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_erorrs(char *s)
{
	if(ft_isalpha(s[0]) == 0)
	{
		printf("export : %s not a valid identifier\n",s);
		exit(1);
	}
}
int 	__check_add(char *s)
{
	int i = 0;
	while(s[i])
	{
		if(s[i] == '+')
			return (0);
		i++;
	}
	return(1);
		
}

int 	__check_key_exit(t_env *lst,char *s)
{
	while(lst)
	{
		if(ft_strcmp(lst->key,s) == 0)
			return (0);
		lst = lst->next;
	}
	return(1);
}

void 	__check_data_exit(t_env *lst,char **s)
{
	while(lst)
	{
		if(ft_strcmp(lst->key,s[0]) == 0)
		{
			//if(lst->data != NULL)
				if(ft_strcmp(lst->data,s[1]))
					lst->data = ft_strdup(s[1]);
		}
		lst = lst->next;
	}
}

void	_add_to_export(t_env *lst, char *s)
{
	int i = 0;
	char **p = ft_split(s,' ');
	if(p[1] == NULL)
		return;
	while(p[i])
		i++;
	int j = 1 ;
	while(j < i)
	{
		check_erorrs(p[j]);
		char **ptr = ft_split(p[j],'='); 
		if( __check_key_exit(lst,ptr[0]))
			add_back(&lst,ft_lstnew(ptr[0],ptr[1]));
		__check_data_exit(lst,ptr);
		j++;
	}	
}

int	main(int ac, char **av, char **env)
{

	t_env *lst;
 	char	**p;
	int j = 0;
   
	ft_isdigit('1');
	while (j < get_len(env))
	{
		p = split_pwd(env, j);
		add_back(&lst,ft_lstnew(p[0],p[1]));
		j++;
	}
	ft_readline(lst,ac,av);
}