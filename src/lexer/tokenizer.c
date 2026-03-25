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
t_token *token_new(t_token_type type, const char *value) {
	t_token *tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = ft_strdup(value);
	if (!tok->value)
		return (free(tok), NULL);
	tok->next = NULL;
	return (tok);
}

static int token_add_back(t_token **tokens, t_token **last, t_token *new_tok) {
	if (!new_tok)
		return (-1);
	if (!*tokens)
		*tokens = new_tok;
	else
		(*last)->next = new_tok;
	*last = new_tok;
	return (0);
}

static t_token *read_operator_token(const char *line, int *i) {
	if (line[*i] == '|')
		return ((*i)++, token_new(T_PIPE, "|"));
	if (line[*i] == '>' && line[*i + 1] == '>')
		return ((*i) += 2, token_new(T_APPEND, ">>"));
	if (line[*i] == '>')
		return ((*i)++, token_new(T_REDIR_OUT, ">"));
	if (line[*i] == '<' && line[*i + 1] == '<')
		return ((*i) += 2, token_new(T_HEREDOC, "<<"));
	if (line[*i] == '<')
		return ((*i)++, token_new(T_REDIR_IN, "<"));
	return (NULL);
}

static t_token *read_word_token(const char *line, int *i, t_sh *sh) {
	char *word;
	t_token *tok;
	int next;

	word = NULL;
	next = read_word(line, *i, &word, sh);
	if (next < 0)
		return (NULL);
	tok = token_new(T_WORD, word);
	free(word);
	if (!tok)
		return (NULL);
	*i = next;
	return (tok);
}

t_token *tokenizer(const char *line, t_sh *sh) {
	t_token *tokens;
	t_token *last;
	t_token *new_tok;
	int i;

	if (!line)
		return (NULL);
	tokens = NULL;
	last = NULL;
	i = 0;
	while (line[i]) {
		i = skipspace(line, i);
		if (!line[i])
			break;
		new_tok = read_operator_token(line, &i);
		if (!new_tok)
			new_tok = read_word_token(line, &i, sh);
		if (token_add_back(&tokens, &last, new_tok) < 0)
			return (free_tokens(tokens), NULL);
	}
	return (tokens);
}
