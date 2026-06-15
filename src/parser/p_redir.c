/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:52:06 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == T_REDIR_IN
		|| type == T_REDIR_OUT
		|| type == T_APPEND
		|| type == T_HEREDOC);
}

void	redir_add_back(t_redir **lst, t_redir *new_node)
{
	t_redir	*tmp;

	if (!new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_redir	*redir_new(t_token_type type, const char *target)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		fatal_malloc_error();
	node->type = type;
	node->target = ft_strdup(target);
	if (!node->target)
	{
		free(node);
		fatal_malloc_error();
	}
	if (type == T_REDIR_IN || type == T_HEREDOC)
		node->fd = 0;
	else
		node->fd = 1;
	node->heredoc_fd = -1;
	node->next = NULL;
	return (node);
}
