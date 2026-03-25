/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wkozlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 21:21:43 by wkozlows          #+#    #+#             */
/*   Updated: 2026/03/25 19:12:05 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_segment(const char *s, int start, int end, char **buf)
{
	char	*piece;

	piece = ft_substr(s, start, end - start);
	if (!piece)
		return (-1);
	if (append_piece(buf, piece) < 0)
	{
		free(piece);
		return (-1);
	}
	free(piece);
	return (0);
}

static int	read_single_quoted(const char *s, int i, char **buf)
{
	int	start;

	start = ++i;
	while (s[i] && s[i] != '\'')
		i++;
	if (!s[i])
		return (ft_putendl_fd("minishell: unclosed quote", 2), -1);
	if (append_segment(s, start, i, buf) < 0)
		return (-1);
	return (i + 1);
}

static int	read_double_quoted(const char *s, int i, char **buf, t_sh *sh)
{
	int	start;

	i++;
	while (s[i] && s[i] != '"')
	{
		if (s[i] == '$')
		{
			if (expand_dollar(s, &i, buf, sh) < 0)
				return (-1);
			continue ;
		}
		start = i;
		while (s[i] && s[i] != '"' && s[i] != '$')
			i++;
		if (append_segment(s, start, i, buf) < 0)
			return (-1);
	}
	if (!s[i])
		return (ft_putendl_fd("minishell: unclosed quote", 2), -1);
	return (i + 1);
}

static int	read_plain_chunk(const char *s, int i, char **buf, t_sh *sh)
{
	int	start;

	while (s[i] && !ft_isspace((unsigned char)s[i]) && !ft_strchr("|<>\"'",
			s[i]))
	{
		if (s[i] == '$')
		{
			if (expand_dollar(s, &i, buf, sh) < 0)
				return (-1);
			continue ;
		}
		start = i;
		while (s[i] && !ft_isspace((unsigned char)s[i]) && !ft_strchr("|<>\"'$",
				s[i]))
			i++;
		if (append_segment(s, start, i, buf) < 0)
			return (-1);
	}
	return (i);
}

int	read_word(const char *s, int i, char **out, t_sh *sh)
{
	char *buf;

	buf = NULL;
	while (s[i] && !ft_isspace((unsigned char)s[i]) && !ft_strchr("|<>", s[i]))
	{
		if (s[i] == '\'')
			i = read_single_quoted(s, i, &buf);
		else if (s[i] == '"')
			i = read_double_quoted(s, i, &buf, sh);
		else
			i = read_plain_chunk(s, i, &buf, sh);
		if (i < 0)
			return (free(buf), -1);
	}
	if (!buf)
		buf = ft_strdup("");
	if (!buf)
		return (-1);
	*out = buf;
	return (i);
}
