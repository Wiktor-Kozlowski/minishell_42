/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_pipeline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:51:58 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/09 03:51:58 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	fill_cmd(t_cmd *cmd, t_token *start, int argc)
{
	t_token *t;
	t_token *redir_token;
	t_redir *r_node;
	int	i;

	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
		return (-1);
	cmd->redirs = NULL;
	cmd->is_builtin = 0;
	i = 0;
	t = start;
	while (t)
	{
		if (t->type == T_PIPE)
			break;
		if (is_redir_token(t->type))
		{
			redir_token = t;
			t = t->next;
			if (!t || t->type != T_WORD)
				return (-1);
			r_node = redir_new(redir_token->type, t->value);
			if (!r_node)
				return (-1);
			redir_add_back(&cmd->redirs, r_node);
			t = t->next;
		}
		else if (t->type == T_WORD)
		{
			cmd->argv[i] = ft_strdup(t->value);
			if (!cmd->argv[i])
				return (-1);
			i++;
			t = t->next;
		}
		else
			t = t->next;
	}
	cmd->argv[i] = NULL;
	cmd->is_builtin = is_builtin_name(cmd->argv[0]);
	return (0);
}

t_pipeline	*cr_pipeline(t_token *tokens)
{
	t_pipeline *pl;

	int cmd_count;
	int i;
	int argc;

	i = 0;

	if (!tokens)
		return (NULL);
	cmd_count = count_commands(tokens);
	pl = malloc(sizeof(t_pipeline));
	if (!pl)
		return (NULL);
	pl->cmd_count = cmd_count;
	pl->cmds = ft_calloc(cmd_count, sizeof(t_cmd));
	if (!pl->cmds)
	{
		free(pl);
		return (NULL);
	}

	while (tokens && i < cmd_count)
	{
		argc = count_args(tokens);
		if (fill_cmd(&pl->cmds[i], tokens, argc) < 0)
		{
			free_pipeline(pl);
			return (NULL);
		}
		tokens = next_cmd_start(tokens);
		i++;
	}
	return (pl);
}