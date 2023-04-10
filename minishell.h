/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:04:10 by afadlane          #+#    #+#             */
/*   Updated: 2023/04/10 01:03:36 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 14
# endif
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
typedef struct minishell
{
	char				*data;
	struct minishell	*next;
	struct minishell	*prev;

}						t_lst; 

char					*get_next_line(int fd);
int						ft_strlen(char *s);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strdup(char *s1);
char					*ft_strchr(char *p, int c);
long					ft_atoi(char *str);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
char					**ft_split(char *s, char c);

#endif