/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:04:10 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/02 19:54:52 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 14
# endif
#include"./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
typedef struct env
{
	char		*data;
	char		*key;
	struct env	*next;
	struct env	*prev;
	int			id;

}				t_env;

int		get_len(char **env);
char	**split_pwd(char **env, int j);
void	_add_to_export(t_env *lst, char *s);
char	*get_next_line(int fd);
t_env	*ft_lstnew(char *s,char *d);
void	add_back(t_env **list, t_env *new);
void    ft_readline(t_env *lst,int ac ,char **av);
int 	ft_strcmp(char *s1, char *s2);
void	sort_export(t_env *tmp, int (*ft_strcmp) (char *, char *));
#endif