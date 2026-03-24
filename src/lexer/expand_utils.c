/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wkozlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:46:06 by wkozlows          #+#    #+#             */
/*   Updated: 2026/03/25 00:50:06 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_start(char c)
{
	if (ft_isalpha((unsigned char)c) || c == '_')
		return (1);
	return (0);
}

int	is_var_char(char c)
{
	if (ft_isalnum((unsigned char)c) || c == '_')
		return (1);
	return (0);
}

int	append_char(char **buf, char c)
{
	char tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (append_piece(buf, tmp));
}
