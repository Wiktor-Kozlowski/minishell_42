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

#include "minishell.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	skipspace(const char *text, int i)
{
	if (!text)
		return (i);
	while (text[i] && ft_isspace((unsigned char)text[i]))
		i++;
	return (i);
}

int	append_piece(char **buf, const char *piece)
{
	char	*joined;

	if (!*buf)
		*buf = ft_strdup(piece);
	else
	{
		joined = ft_strjoin(*buf, piece);
		free(*buf);
		*buf = joined;
	}
	if (!*buf)
		return (-1);
	return (0);
}
