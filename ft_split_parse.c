
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:57:13 by marvin            #+#    #+#             */
/*   Updated: 2023/04/23 17:57:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     word_len(char *s, char c)
{
    int     i;
    char    ch;

    i = 0;
    while (s[i] && s[i] != c)
    {
        if (s[i] == '\'' || s[i] == '\"')
        {
            ch = s[i++];
            while (s[i] && s[i] != ch)
                i++;
        }
        i++;
    }
    return (i);
}

char   *full_charge(char *s, char c)
{
    int     i;
    char    *w;
    int     len;

    i = 0;
    // printf ("str == %s\n", s);
    len = word_len(s, c);
    w = malloc(sizeof(char) * len + 1);
    while (i < len)
    {
        w[i] = s[i];
        i++;
    }
    w[i] = '\0';
    return (w);
} 

char    **ft_charge(char **s, char *s1, char c)
{
    int     j;
    int     len;
    int     start;
    int     i;

    j = 0;
    i = 0;
    start = -1;
    len = count_strs(s1, c);

    while (s1[i])
    {
        if (s1[i] != c && start < 0)
            start = i;
        else if ((s1[i] == c || i == ft_strlen(s1) - 1) && start >= 0)
        {
            s[j] = full_charge((s1 + start), c);
            start = -1;
            if (!s[j])
				return (ft_free(s), NULL);
            j++;
        }
        i++;
    }
    s[j] = NULL;
    return (s);
}

int     count_strs(char *str, char c)
{
    int     i;
    int     num;
    char    ch;
    

    i = 0;
    num = 1; // i intiall by 1 becouse str is not empty
    while (str[i])
    {
        if (str[i] == c)
        {
            while (str[i] == c)
                i++;
            num++;
        }
        if (str[i] == '\'' || str[i] == '\"')
        {
            ch = str[i++];
            while (str[i] && str[i] != ch)
                i++;
        }
        if (str[i])
            i++;
    }
    return (num);
}

char    **ft_split_parse(char *str, char c)
{
    int     i;
    char    **s;
    
    i = 0;
    if (!str|| !str[0])
        return NULL;
    s = malloc(sizeof(char *) * (count_strs(str, c) + 1));
    if (!s)
        return NULL;
    s = ft_charge(s, str, c);
    return (s);
}

// int     word_len(char *s, char c)
// {
//     int     i;
//     char    ch;

//     i = 0;
//     while (s[i] && s[i] != c)
//     {
//         if (s[i] == '\'' || s[i] == '\"')
//         {
//             ch = s[i++];
//             while (s[i] && s[i] != ch)
//                 i++;
//         }
//         i++;
//     }
//     return (i);
// }

// char   *full_charge(char *s, char c)
// {
//     int     i;
//     char    *w;
//     int     len;

//     i = 0;
//     len = word_len(s, c);
//     w = malloc(sizeof(char) * len + 1);
//     while (i < len)
//     {
//         w[i] = s[i];
//         i++;
//     }
//     w[i] = '\0';
//     return (w);
// } 

// char    **ft_charge(char **s, char *s1, char c)
// {
//     int     j;
//     int     len;
//     int     count;

//     j = 0;
//     len = count_strs(s1, c);
//    // src = malloc(sizeof(char *) * len + 1);
//    // printf ("this is the problem === %s\n", s);
//    // printf ("1st start == %d && end == %d\n", start, end);
//     while (*s1)
//     {
//         count = 0;
//         while (*s1 && *s1 == c)
//             s1++;
//         if (*s1)
//         {
//             s[j] = full_charge(s1, c);
//             if (!s[j])
// 				return (ft_free(s, j), NULL);
//             j++;
//         }
//         count = word_len(s1, c);
//         while (*s1 && count)
//         {
//             s1++;
//             count--;
//         }
//     }
//     s[len] = NULL;
//     return (s);
// }

// int     count_strs(char *str, char c)
// {
//     int i;
//     int num;

//     i = 0;
//     num = 1; // i intiall by 1 becouse str is not empty
//     while (str[i])
//     {
//         if (str[i] == c)
//         {
//             while (str[i] == c)
//                 i++;
//             num++;
//         }
//         if (str[i] == '\'' || str[i] == '\"')
//         {
//             c = str[i++];
//             while (str[i] != c)
//                 i++;
//         }
//         if (str[i])
//             i++;
//     }
//     return (num);
// }

// char    **ft_split_parse(char *str, char c)
// {
//     int     i;
//     char    **s;
//     int     num;
//     char    n;
    
//     i = 0;
//     if (!str|| !str[0])
//         return NULL;
//     printf ("********%d*******\n", count_strs(str, c));
//     s = malloc(sizeof(char *) * count_strs(str, c) + 1);
//     if (!s)
//         return NULL;
//     s = ft_charge(s, str, c);
//     return (s);
// }
