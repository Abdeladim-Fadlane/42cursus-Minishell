/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:04:10 by afadlane          #+#    #+#             */
/*   Updated: 2023/05/24 22:12:39 by afadlane         ###   ########.fr       */
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
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define OUT 1
# define INF 2
# define DEL 3
# define APE 4
# define PIPE 1

typedef struct signal
{
	int				status;
	int				signal;
}					t_sig;

t_sig				*sig;
typedef struct object
{
	char			*s;
	struct object	*next;

}					t_object;

typedef struct redir
{
	int				type;
	char			*out;
	char			*in;
	char			*limiter;
	struct redir	*next;
}					t_redir;

typedef struct content
{
	int				quote;
	int				type;
	char			*content;
}					t_content;

typedef struct cmd
{
	char			*cmd;
	struct cmd		*next;

}					t_cmd;

typedef struct shell
{
	t_redir			*redirct;
	t_cmd			*cmd;
	int				index;
	char			**all_cmds;
	int				pipe;
	struct shell	*next;
	int				in_id;
	int				out_id;
	int				pid;
}					t_minishell;

typedef struct env
{
	char			*data;
	char			*key;
	struct env		*next;
	struct env		*prev;
	int				id;
	int				flag_fd;
	int				fd[2];
	int				fd2[2];
	int				n;
	int				fd1;

}					t_env;

char				**pass_cmds(t_cmd *cmd);
void				ft_print(char **s);
void				ft_free(char **strs);
t_minishell			*parsing(char **line);
t_minishell			*ft_lstneww(char *s, int i, int pipe);
void				ft_add_back(t_minishell **lst, t_minishell *addnew);
t_redir				*ft_lastt(t_redir *lst);
t_minishell			*ft_last_shell(t_minishell *lst);
void				add_redir(t_redir **lst, t_redir *new);
t_redir				*new_redir(t_content *content);
t_content			*pars_w(char *s, int type);
char				*charge_str(char c, char *src);
char				*expand(char *s, int type, char *str);
void				go_to_parse(char **s, t_minishell *new);
char				*detach_rediec(char *str, char *line);
char				**ft_split_parse(char *str, char c);
char				**ft_charge(char **src, char *s1, char c);
char				*full_charge(char *s, char c);
int					word_len(char *s, char c);
int					count_strs(char *str, char c);
int					ft_strlen(const char *s);
int					all_redric(char *src);
char				*detach_rediec(char *str, char *line);
int					handle_single(char c, char *line, int i);
int					hande_double(char c, char *line, int i);
int					count_char(char *str, char c);
int					check_qouts(char *line, char c);
int					check_redir(char *s);
int					handle_pipe(char *str);
int					check_syntext(char *line);
char				**parse_to_part(char *line);
void				add_back_cmd(t_cmd **cmd, t_cmd *new);
t_cmd				*ft_last_cmd(t_cmd *cmd);
t_cmd				*new_cmd(char *str);

void				first_proccess(t_env *lst, char **ptr, char **cmd,
						t_minishell *p);
void				midlle_proccess(t_env *lst, char **ptr, char **cmd,
						t_minishell *p);
void				last_proccess(t_env *lst, char **ptr, char **cmd,
						t_minishell *p);
void				one_command(char **ptr, char **cmd, t_minishell *p,
						t_env *lst);
void				main_herdoc(t_env *p, t_object *obj);
t_object			*t_lstlast(t_object *lst);
t_env				*ft_lstnew(char *s, char *d);
t_object			*t_lstnew(char *s);
int					__built__in__(t_env *lst, t_minishell *list, int i);
int					ft_strcmp(char *s1, char *s2);
int					lstsize(t_minishell *list);
int					ft_lstsize(t_env *list);
char				*get_cmd(char **ptr, char *lst, t_env *p);
void				handle_clr();
void				ft_lstadd_back(t_env **lst, t_env *new);
void				__main__(t_env *lst, t_minishell *list);
void				t_lstadd_back(t_object **lst, t_object *new);
void				ft_free(char **p);
char				**__split__(char **env, int j);
void				__add__to__export__(t_env *lst, t_minishell *s);
char				*get_next_line(int fd);
void				her_doc(char *s, t_env *p);
char				**get_env(t_env *p);
void				pipex(t_minishell *lst, t_env *p, t_object *obj);
void				__pwd__(int k, int fd, int g);
char				*check_env(t_env *p);
void				put_str(char *s, int fd);
void				__echo__(t_minishell *lst, int k, int fd, int y);
void				get_index_pwd(t_env *lst, char *path, char *s);
char				*get_user(t_env *lst);
void				__cd__(char *str, t_env *p);
char				**__split__(char **env, int j);
void				__print__env__(t_env *p, int k, int fd, int j);
void				__print__export__(t_env *p, int k, int fd, int fdd);
void				__unset__(t_env *lst, t_minishell *ptr);
void				__readline__(t_env *lst);
void				main_herdoc(t_env *p, t_object *obj);
void				exitstatus(void);
void				error(char *s);
char				*check_env(t_env *p);
void				open_append(char *s, t_minishell *lst);
void				open_outfile(char *s, t_minishell *lst);
void				open_infile(char *s, t_minishell *lst);
void				check_erorrs(char *s);
#endif
