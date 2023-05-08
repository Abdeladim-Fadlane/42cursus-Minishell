/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:15 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/07 20:19:42 by afadlane         ###   ########.fr       */
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



void 	expand_data(t_env *lst,char **s)
{
	while(lst)
	{
		if(ft_strcmp(lst->key,s[0]) == 0)
		{
				if(ft_strcmp(lst->data,s[1]))
					lst->data = ft_strdup(s[1]);
		}
		lst = lst->next;
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

void 	__check_data_exit(t_env *lst,char **s,int flag)
{
	
	while(lst)
	{
		if(ft_strcmp(lst->key,ft_split(s[0],'+')[0]) == 0)
		{
			if(ft_strcmp(lst->data,s[1]) && flag == 0)
			{	
				char *d = ft_strdup(lst->data);
				lst->data = ft_strjoin(d,s[1]);
			}
			else if(ft_strcmp(lst->data,s[1]))
				lst->data = ft_strdup(s[1]);
		}
		lst = lst->next;
	}
}

void	__add__to__export__(t_env *lst, char *s)
{
	char **p = ft_split(s,' ');
	if(p[1] == NULL)
		return;
	int flag = 1;
	int j = 1 ;
	while(p[j])
	{
		check_erorrs(p[j]);
		char **ptr = ft_split(p[j],'=');
		char *s = ft_split(ptr[0],'+')[0];
		if( __check_key_exit(lst,s))
			add_back(lst,ft_lstnew(s,ptr[1]));
		if(__check_add(ptr[0]) == 0)
				flag = 0;
		__check_data_exit(lst,ptr,flag);
		j++;
	}	
}

void	__main__(t_env *lst,char **env)
{
	char	**p;
	int j = 0;
   
	while (j < get_len(env))
	{
		p = split_pwd(env, j);
		add_back(lst,ft_lstnew(p[0],p[1]));
		j++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_env lst;
	__main__(&lst,env);
	__built__in__(&lst,ac,av);
}