/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:20:41 by marvin            #+#    #+#             */
/*   Updated: 2023/04/19 00:20:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_char(char *str, char c)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

int     check_qouts(char *line, char c)
{
    int     i;
    int     count;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (line[i] == c)
            count++;
        i++;
    }
    return (count % 2);
}

int     check_redir(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '>')
        {
            i++;
            if (!s[i] || (s[i] == '>' && !s[i]) || s[i] == '<' || (s[i] == '>' && s[i + 1] == '>'))
                return (1);
        }
        if (s[i] == '<')
        {
            i++;
            if (!s[i] || (s[i] == '<' && !s[i]) || s[i] == '>' || (s[i] == '<' && s[i + 1] == '<'))
                return (1);
        }
        i++;
    }
    return 0;
}

int     handle_pipe(char *str)
{
    int     i;
    char    ch;
    char    *h;

    i = 0;

    h = ft_strtrim(str, " ");
    if (h[0] == '|' || h[ft_strlen(h) - 1]== '|')
        return (1);
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            ch = str[i];
            while (str[i] && str[i] != ch)
                i++;
        }
        if (!str[i] && str[i] == '|')
            return 1;
        i++;
    }
    return 0;
}

int     check_syntext(char *line)
{
    int i;
    char    *str;

    i = 0;
    str = ft_strdup(line);
    str = ft_strtrim(line, "\'"); 
    str = ft_strtrim(line, "\"");
   // printf ("str == %s \t\n", str);
    if (count_char(str, '\'') + count_char(str, '\"') == ft_strlen(str))
        return (404);
    if (check_qouts(str, '\'') == 1 || check_qouts(str, '\"') == 1)
        return (404);
    if (check_redir(str) == 1)
        return (404);
    if (handle_pipe(str) == 1)
         return (404);
    while (line[i])
    {
        if (line[i] == '>' || line[i] == '<')
        {
            i++;
            if (line[i] && line[i] == ' ')
                i++;
            if ((line[i] == '>' || line[i] == '<') && line[i - 1] == ' ')
                return (404);
        }
        i++;
    }
    return 0;
}
