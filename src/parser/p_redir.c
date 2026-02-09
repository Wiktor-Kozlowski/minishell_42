/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:52:06 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/09 03:52:06 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

/* === sprawdza, czy dany typ tokena jest redirekcją (<, >, >>, <<) === */
int	is_redir_token(t_token_type type)
{
	return (type == T_REDIR_IN
		|| type == T_REDIR_OUT
		|| type == T_APPEND
		|| type == T_HEREDOC);
}

/* === dopisuje nową redirekcję na koniec listy redirów w jednej komendzie === */
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

/* === tworzy nowy węzeł redirekcji (typ, target, domyślny fd, next = NULL) === */
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
	node->next = NULL;
	return (node);
}

/*
int is_valid_var(char *c)
{
    int i;

    i = 1;
    if (!ft_isalpha((unsigned char)c[0]) || c[0] == '_')
        return (0);
    while (c[i])
    {
        if (ft_isalnum((unsigned char)c[i]) || c[i] == '_')
            i++;
        else
            return (0);
    }
    return (1);
}
*/