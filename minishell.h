/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:04:10 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/07 20:25:31 by afadlane         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct env
{
	char		*data;
	char		*key;
	struct env	*next;
	struct env	*prev;
	int			id;

}				t_env;

typedef struct object
{
	char	**envp;
	int		pid2;
	int		pid3;
	int		pid;
	char	**p;
	int		fd[2];
	int		flag_fd;
}			t_object;

void		ft_error(void);
void		__pipex__(t_env *lst ,char *s);
void		first_proccess(char **av, char **ptr, t_object *lst);
void		second_proccess(char **av, char **ptr2, t_object *lst, int k);
void		midlle_proccess(char **av, char **ptr2, t_object *lst, int k);
char		*get_cmd(char **ptr, char **p);
void		ft_free(char **p);
void		ft_error1(void);
int			get_len(char **env);
char		**split_pwd(char **env, int j);
void		__add__to__export__(t_env *lst, char *s);
char		*get_next_line(int fd);
void		add_back(t_env *list, t_env *new);
void    	__built__in__(t_env *lst,int ac ,char **av);
int 		ft_strcmp(char *s1, char *s2);
void		__pipex__(t_env *lst ,char *s);
void    	__built__(t_env *lst ,char *buff);
t_env		*ft_lstnew(char *s,char *d);
// void	sort_export(t_env *tmp, int (*ft_strcmp) (char *, char *));
#endif
