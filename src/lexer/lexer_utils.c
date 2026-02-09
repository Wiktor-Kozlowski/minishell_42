/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:51:23 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/09 03:51:23 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <include/minishell.h>

/* === pomocnicze: append_piece, read_quoted, read_word === */

int  append_piece(char **buf, const char *piece)
{
    char    *joined;

    if (!*buf)
        *buf = ft_strdup(piece);
    else
    {
        joined = ft_strjoin(*buf, piece);
        free(*buf);
        *buf = joined;
    }
    return (*buf ? 0 : -1);
}

int  read_quoted(const char *s, int i, char quote, char **buf)
{
    int     start;
    char    *piece;

    start = ++i;
    while (s[i] && s[i] != quote)
        i++;
    if (!s[i])
    {
        fprintf(stderr, "minishell: unclosed quote\n");
        return (-1);
    }
    piece = ft_substr(s, start, (size_t)(i - start));
    if (!piece || append_piece(buf, piece) < 0)
    {
        free(piece);
        return (-1);
    }
    free(piece);
    return (i + 1);
}

int  read_word(const char *s, int i, char **out)
{
    char    *buf;
    char    *piece;
    int     start;

    buf = NULL;
    while (s[i] && !ft_isspace((unsigned char)s[i]) && !ft_strchr("|<>", s[i]))
    {
        if (s[i] == '\'' || s[i] == '\"')
        {
            i = read_quoted(s, i, s[i], &buf);
            if (i < 0)
            {
                free(buf);
                return (-1);
            }
        }
        else
        {
            start = i;
            while (s[i] && !ft_isspace((unsigned char)s[i])
                && !ft_strchr("|<>", s[i]) && s[i] != '\'' && s[i] != '\"')
                i++;
            piece = ft_substr(s, start, (size_t)(i - start));
            if (!piece || append_piece(&buf, piece) < 0)
            {
                free(piece);
                free(buf);
                return (-1);
            }
            free(piece);
        }
    }
    *out = (buf ? buf : ft_strdup(""));
    return (i);
}