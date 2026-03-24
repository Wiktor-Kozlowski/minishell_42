/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/02/09 03:51:23 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/09 03:51:23 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	append_piece(char **buf, const char *piece)
{
	char *joined;

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
