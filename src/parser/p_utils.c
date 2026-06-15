/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:52:16 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/09 03:52:16 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_token *tok)
{
	int	count;

	if (!tok)
		return (0);
	count = 1;
	while (tok)
	{
		if (tok->type == T_PIPE)
			count++;
		tok = tok->next;
	}
	return (count);
}

int	count_args(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != T_PIPE)
	{
		if (is_redir_token(tok->type))
		{
			tok = tok->next;
			if (tok)
				tok = tok->next;
		}
		else if (tok->type == T_WORD)
		{
			count++;
			tok = tok->next;
		}
		else
			tok = tok->next;
	}
	return (count);
}

t_token	*next_cmd_start(t_token *token)
{
	while (token)
	{
		if (token->type == T_PIPE)
			return (token->next);
		token = token->next;
	}
	return (NULL);
}

int	is_builtin_name(const char *name)
{
	if (!name)
		return (0);
	if (ft_strncmp(name, "echo", 5) == 0 && ft_strlen(name) == 4)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0 && ft_strlen(name) == 2)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0 && ft_strlen(name) == 3)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0 && ft_strlen(name) == 6)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0 && ft_strlen(name) == 5)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0 && ft_strlen(name) == 3)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0 && ft_strlen(name) == 4)
		return (1);
	return (0);
}
