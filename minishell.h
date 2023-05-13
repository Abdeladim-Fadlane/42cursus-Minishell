/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:04:10 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/14 00:01:12 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 14
# endif
# include "./libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

# define OUT 1
# define INF 2
# define DEL 3
# define APE 4
# define PIPE 1

typedef struct redir
{
	int type;
	char *out;
	char *in;
	char *limiter;
	struct redir *next;
} t_redir;

typedef struct content
{
	int		quote;
	int		type;
	char	*content;
} t_content;

typedef struct cmd
{
	char		*cmd;
	struct cmd	*next;
	
}t_cmd;

typedef struct shell
{
	t_redir *redirct;
	t_cmd 	*cmd;
	int 	index;
	char 	**all_cmds;
	int		pipe;
	struct shell *next;
	int in_id ;
	int out_id ;
	int pid;

} t_minishell;

typedef struct env
{
	char		*data;
	char		*key;
	struct env	*next;
	struct env	*prev;
	int			id;
	int			flag_fd;
	int			fd[2];
}				t_env;

typedef struct object
{
	char		**envp;
	int			pid2;
	int			pid3;
	int			pid;
	char		**p;

	
}t_object;
//parsing functions***
char	**pass_cmds(t_cmd *cmd);
void		ft_print(char **s);
void		ft_free(char **strs);
t_minishell	*parsing(char **line);
t_minishell	*ft_lstneww(char *s, int i, int pipe);
void		ft_add_back(t_minishell **lst, t_minishell *addnew);
t_redir 	*ft_lastt(t_redir *lst);
t_minishell	*ft_last_shell(t_minishell *lst);
void     	add_redir(t_redir **lst, t_redir *new);
t_redir 	*new_redir(t_content *content);
t_content   *pars_w(char *s, int type);
char		*charge_str(char c, char *src);
char    	*expand(char *s, int type, char *str);
void		go_to_parse(char **s, t_minishell *new);
char		*detach_rediec(char *str, char *line);
char		**ft_split_parse(char *str, char c);
char		**ft_charge(char **src, char *s1, char c);
char		*full_charge(char *s, char c);
int			word_len(char *s, char c);
int			count_strs(char *str, char c);
int			ft_strlen(const char *s);
int			all_redric(char *src);
char		*detach_rediec(char *str, char *line);
int			handle_single(char c, char *line, int i);
int			hande_double(char c, char *line, int i);
int			count_char(char *str, char c);
int			check_qouts(char *line, char c);
int			check_redir(char *s);
int			handle_pipe(char *str);
int			check_syntext(char *line);

void	add_back_cmd(t_cmd **cmd, t_cmd *new);
t_cmd   	*ft_last_cmd(t_cmd *cmd);
t_cmd	*new_cmd(char *str);
// char		*ft_strdup(const char *source);
// char		*ft_substr(char const *s, unsigned int start, size_t len);
// char		*ft_strtrim(char *s1, char *set);
// char		*ft_substr(char const *s, unsigned int start, size_t len);
void print_data(t_minishell *shell);

/// exute
void ft_lstadd_back(t_env **lst, t_env *new);
void __main__(t_env *lst, char **env, t_minishell *list, char *buff);
void ft_error(void);
void			x__(t_env *lst, char *s);
int ft_lstsize(t_env *list);
void ft_free(char **p);
void			ft_error1(void);
char			**__split__(char **env, int j);
void			__add__to__export__(t_env *lst, char *s);
char			*get_next_line(int fd);
void			aadd_back(t_env **list, t_env *new);
void		add_back(t_env *lst, t_env *new);
int				ft_strcmp(char *s1, char *s2);
//void			__pipex__(t_env *lst, char *s);
void	__built__in__(t_env *lst, char *buff,char **env ,t_minishell *list);
t_env			*ft_lstnew(char *s, char *d);
void pipex(t_minishell *lst,t_env *p,char **env);
// void	sort_export(t_env *tmp, int (*ft_strcmp) (char *, char *));
#endif
