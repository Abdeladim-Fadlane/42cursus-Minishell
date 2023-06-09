/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:04:10 by afadlane          #+#    #+#             */
/*   Updated: 2023/06/09 11:20:06 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 14
# endif
# include "./libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
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
	int				pid;
	int				flag;
	int				dude;
	int				j;
	int				ft_flag;
	int				sst;
	int				start;
	int exp;
}					t_sig;

t_sig				*g_sig;
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
	char			**str;
	int				pipe;
	struct shell	*next;
	int				in_id;
	int				out_id;
	int				pid;
	int				dell;
	char			**s1;
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
	int				d;
	int				ss;
	int				fd1;
	char			**ptr;
	char			*ptr1;
	char			*s;
	char			**p;
	char *sub;
}					t_env;


int					skip_qoute(char *s, int *i, int k);
void				check_close_qotes(char *s, int *d, int *ss);
void				ft_print(char **s);
int					check(char *set, char s);
int					ft_strrchr_v2(const char *s, char c);
int					is_valid(char c);
char				*remove_quotes(char *str, int i, int s, int d);
char				*ft_strjoinn(char *s1, char *s2);
int					check_delmiter(char *h);
void				ft_add_back_env(t_env **lst, t_env *new);
t_env				*ft_last_env(t_env **list);
t_env				*ft_lstnew_env(char *s1, char *s2);
int					len_env(char **en);
char				**array_env(char **env, int j);
char				*ft_strcpy(char *dest, char *src);
char				*env_value(char *s1, char *str, t_env *env, int *i);
void				ft_print(char **s);
int					aft_strrchr(const char *s, char c);
void				ft_free(char **strs);
t_minishell			*parsing(char **line, t_env *env);
t_minishell			*ft_lstneww(char *s, int i, int pipe, t_env *env);
void				ft_add_back(t_minishell **lst, t_minishell *addnew);
t_redir				*ft_last(t_redir *lst);
t_minishell			*ft_last_shell(t_minishell *lst);
void				add_redir(t_redir **lst, t_redir *new);
t_redir				*new_redir(t_content *content);
t_content			*pars_w(char *s, int type, t_env *env, int j);
t_cmd				*new_cmd(char *str);
t_cmd				*ft_last_cmd(t_cmd *cmd);
void				add_back_cmd(t_cmd **cmd, t_cmd *new);
int					count_cmd(t_cmd *cmd);
char				**pass_cmds(t_cmd *cmd);
void				add_back_cmd(t_cmd **cmd, t_cmd *new);
char				*charge_str(char c, char *src);
char				*expand(char *s, char *str, t_env *env, int j);
void				go_to_parse(char **s, t_minishell *new, t_env *env);
char				**ft_split_parse(char *str, char c);
char				**ft_charge(char **s, char *s1, char c, int i);
char				*full_charge(char *s, char c);
int					word_len(char *s, char c);
int					count_strs(char *str, char c);
int					all_redric(char *src, int i, int j);
void				detach_rediec(char *str, char *line, int i, int j);
int					handle_single(char c, char *line, int i);
int					hande_double(char c, char *line, int j, int *i);
int					count_char(char *str, char c);
int					check_qouts(char *line, char c);
int					check_redir(char *s, int i);
int					handle_pipe(char *str, int i);
int					check_syntext(char *line);
void				ft_free_v2(char **s, int j);
int					check_redir_v2(char *s);
int					content_count(char **s);
char        		*readline(const char *);

void				first_proccess(t_env *lst, char **cmd, t_minishell *p);
void				midlle_proccess(t_env *lst, char **cmd, t_minishell *p);
int					last_proccess(t_env *lst, char **cmd, t_minishell *p);
void				one_command(char **cmd, t_minishell *p, t_env *lst);
void				main_herdoc(t_env *p, t_object *obj);
t_object			*t_lstlast(t_object *lst);
t_env				*ft_lstnew(char *s, char *d);
t_object			*t_lstnew(char *s);
int					__built__in__(t_env *lst, t_minishell *list, int i);
int					ft_strcmp(char *s1, char *s2);
int					lstsize(t_minishell *list);
int					ft_lstsize(t_env *list);
char				*get_cmd(char **ptr, char *lst, t_env *p);
void				handle_clr(int n);
void				ft_lstadd_back(t_env **lst, t_env *new);
void				__main__(t_env *lst, t_minishell *list);
void				t_lstadd_back(t_object **lst, t_object *new);
void				ft_free(char **p);
char				**__split__(char **env, int j);
void				__add__to__export__(t_env *lst, t_minishell *s,int j);
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
void				exitstatus(int pid);
void				error(char *s);
char				*check_env(t_env *p);
int				open_append(char *s, t_minishell *lst);
int				open_outfile(char *s, t_minishell *lst);
int				open_infile(char *s, t_minishell *lst);
int					check_erorrs(char *s,char *k);
char				*ffree(char **strs, char *s);
int					check_flag(char *s);
int	__check_add(char *s);
int	check_erorrs_export(char *s,char *d);
char **get_var(char *s);
void	norm_export(t_env *lst);
void	__check_data_exit(t_env *lst, char **s, int flag);
void	ft_exit(t_minishell *list);
#endif
