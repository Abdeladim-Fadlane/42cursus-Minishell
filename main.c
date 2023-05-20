/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:01:15 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/20 22:56:20 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	open_append(char *s,t_minishell *lst)
{
	lst->out_id = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (lst->out_id == -1)
		perror(s);
} 

// void	her_doc(char *s,t_minishell *lst,t_env *p)
// {
// 	(void)lst;
// 	int pid = fork();
// 	pipe(p->fd);
// 	int i = 0;
	
// 	if (pid == 0)
// 	{
// 		while (1)
// 		{
// 			//id = open("herdok")
// 			int fd = open()
// 			char *buff = readline(">");
// 			ft_putstr_fd(buff, fd);
// 		// 				char s1[10];
// 		// read(p->fd[0],s1,6);
// 		// s1[9] = '\0';
// 		// printf("--------%s--------\n", s1);
// 			if (buff == NULL)
// 			{
// 				free(buff);
// 				exit(0);
// 			}
// 			if (buff[0] == '\0')
// 			{
// 				free(buff);
// 				continue ;
// 			}
// 			if(ft_strcmp(s,buff) == 0)

// 				exit(0);
// 		}	
// 	}
// 	dup2p->(p->fd[0], 0);
// 	//dup2(p->in_id, 0);
// 	// if (get_cmd(ptr,cmd[0],lst) == NULL)
// 	// 	error(cmd[0]);
// 	char **s = {"cat", "-e"};
// 	execve();
// 	close(p->fd[1]);
// 	waitpid(pid, &i, 0);
// }
void	check_erorrs(char *s)
{
	if (ft_isalpha(s[0]) == 0)
	{
		printf("export : %s not a valid identifier\n", s);
		exit(1);
	}
}

int	__check_key_exit(t_env *lst, char *s)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, s) == 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void	expand_data(t_env *lst, char **s)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, s[0]) == 0)
		{
			if (ft_strcmp(lst->data, s[1]))
				lst->data = ft_strdup(s[1]);
		}
		lst = lst->next;
	}
}

int	__check_add(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

void	__check_data_exit(t_env *lst, char **s, int flag)
{
	char	*d;

	while (lst)
	{
		if (ft_strcmp(lst->key, ft_split(s[0], '+')[0]) == 0)
		{
			if (flag == 0)
			{
				if(lst->data == NULL)
					lst->data = s[1];
				else
				{
					d = lst->data;
					lst->data = ft_strjoin(d, s[1]);
				}
			}
			else if (flag)
				lst->data = s[1];
		}
		lst = lst->next;
	}
	
}

void	__add__to__export__(t_env *lst, t_minishell *list)
{
	int		flag;
	int		j;
	char	**ptr;
	char	*str;

	if (list->all_cmds[1] == NULL)
		return ; 
	j = 1;
	while (list->all_cmds[j])
	{
		flag = 1;
		check_erorrs(list->all_cmds[j]);
		ptr = ft_split(list->all_cmds[j], '=');
		str = ft_split(ptr[0], '+')[0];
		if (__check_key_exit(lst, str))
			ft_lstadd_back(&lst, ft_lstnew(str, ptr[1]));
		if (__check_add(ptr[0]) == 0)
			flag = 0;
		__check_data_exit(lst, ptr, flag);
		j++;
	}
}

void	__main__(t_env *lst, char **env,t_minishell *list)
{
	char *s;
	t_minishell *p = list;
	lst->n = 0;
	while (list)
	{
		while (list->redirct)           // " This is the way "
		{
			if (list->redirct->type == INF)
				open_infile(list->redirct->in,list);
			if (list->redirct->type == OUT)
				open_outfile (list->redirct->out,list);
			if (list->redirct->type == APE)
				open_append (list->redirct->out,list);
			if (list->redirct->type == DEL)
			{
				lst->n = 1;
				s = list->redirct->limiter;	
			}
			list->redirct = list->redirct->next;
		}
		list = list->next;
	}
	// if(lst->n == 1)
	// {	
	// 	her_doc(s,p,lst);
	// 	if(!p->all_cmds[0])
	// 		return;
	// }
	pipex(p,lst,env);
											// " This is the way "
}
