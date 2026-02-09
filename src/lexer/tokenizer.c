/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:51:36 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/09 03:51:36 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ============ token_new / token_free ============ */

t_token *token_new(t_token_type type, const char *value)
{
    t_token *t;

    t = (t_token *)malloc(sizeof(t_token));
    if (!t)
        return (NULL);
    t->type = type;
    t->value = ft_strdup(value);
    if (!t->value)
    {
        free(t);
        return (NULL);
    }
    t->next = NULL;
    return (t);
}




/* ============ NOWA WERSJA tokenize: zwraca t_token* ============ */

t_token *tokenize(const char *line)
{
    t_token *tokens;
    t_token *last;
    t_token *new_tok;
    char    *word;
    int     i;
    int     ni;

    tokens = NULL;
    last = NULL;
    if (!line)
        return (NULL);
    i = 0;
    while (line[i])
    {
        i = skipspace(line, i);
        if (!line[i])
            break ;
        if (line[i] == '|')
        {
            new_tok = token_new(T_PIPE, "|");
            i++;
        }
        else if (line[i] == '>' && line[i + 1] == '>')
        {
            new_tok = token_new(T_APPEND, ">>");
            i += 2;
        }
        else if (line[i] == '>')
        {
            new_tok = token_new(T_REDIR_OUT, ">");
            i++;
        }
        else if (line[i] == '<' && line[i + 1] == '<')
        {
            new_tok = token_new(T_HEREDOC, "<<");
            i += 2;
        }
        else if (line[i] == '<')
        {
            new_tok = token_new(T_REDIR_IN, "<");
            i++;
        }
        else
        {
            word = NULL;
            ni = read_word(line, i, &word);
            if (ni < 0)
            {
                // free tokens built so far
                free_tokens(tokens);
                return (NULL);
            }
            new_tok = token_new(T_WORD, word);
            free(word);
            i = ni;
        }
        if (!new_tok)
        {
            free_tokens(tokens);
            return (NULL);
        }
        if (!tokens)
        {
            tokens = new_tok;
            last = new_tok;
        }
        else
        {
            last->next = new_tok;
            last = new_tok;
        }
    }
    return (tokens);
}
