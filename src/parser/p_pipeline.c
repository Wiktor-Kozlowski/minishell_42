/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_pipeline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:51:58 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_redir(t_cmd *cmd, t_token **tp)
{
	t_token	*redir_token;
	t_redir	*r_node;

	redir_token = *tp;
	*tp = (*tp)->next;
	if (!*tp || (*tp)->type != T_WORD)
		return (-1);
	r_node = redir_new(redir_token->type, (*tp)->value);
	if (!r_node)
		return (-1);
	redir_add_back(&cmd->redirs, r_node);
	*tp = (*tp)->next;
	return (0);
}

static int	fill_tokens(t_cmd *cmd, t_token *t, int *ip)
{
	while (t && t->type != T_PIPE)
	{
		if (is_redir_token(t->type))
		{
			if (fill_redir(cmd, &t) < 0)
				return (-1);
		}
		else if (t->type == T_WORD)
		{
			cmd->argv[*ip] = ft_strdup(t->value);
			if (!cmd->argv[*ip])
				return (-1);
			(*ip)++;
			t = t->next;
		}
		else
			t = t->next;
	}
	return (0);
}

static int	fill_cmd(t_cmd *cmd, t_token *start, int argc)
{
	int	i;

	cmd->argv = ft_calloc(argc + 1, sizeof(char *));
	if (!cmd->argv)
		return (-1);
	cmd->redirs = NULL;
	cmd->is_builtin = 0;
	i = 0;
	if (fill_tokens(cmd, start, &i) < 0)
		return (-1);
	cmd->argv[i] = NULL;
	cmd->is_builtin = is_builtin_name(cmd->argv[0]);
	return (0);
}

t_pipeline	*cr_pipeline(t_token *tokens)
{
	t_pipeline	*pl;
	int			i;

	if (!tokens)
		return (NULL);
	pl = malloc(sizeof(t_pipeline));
	if (!pl)
		return (NULL);
	pl->cmd_count = count_commands(tokens);
	pl->cmds = ft_calloc(pl->cmd_count, sizeof(t_cmd));
	if (!pl->cmds)
		return (free(pl), NULL);
	i = 0;
	while (tokens && i < pl->cmd_count)
	{
		if (fill_cmd(&pl->cmds[i], tokens, count_args(tokens)) < 0)
			return (free_pipeline(pl), NULL);
		tokens = next_cmd_start(tokens);
		i++;
	}
	return (pl);
}
