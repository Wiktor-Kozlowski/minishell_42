/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:52:26 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/09 03:52:26 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/* === zwalnia listę tokenów połączoną przez t_token->next === */
void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head->value);
		free(head);
		head = next;
	}
}

/* === zwalnia tablicę argv zakończoną NULL-em === */
void	free_argv(char **argv)
{
	size_t	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/* === zwalnia listę przekierowań t_redir === */
void	free_redirs(t_redir *r)
{
	t_redir	*tmp;

	while (r)
	{
		tmp = r->next;
		free(r->target);
		free(r);
		r = tmp;
	}
}

/* === zwalnia jedną komendę: **argv + redirs === */
void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	free_redirs(cmd->redirs);
}

/* === zwalnia cały pipeline: wszystkie komendy i samą strukturę === */
void	free_pipeline(t_pipeline *pl)
{
	int	i;

	if (!pl)
		return ;
	if (pl->cmds)
	{
		i = 0;
		while (i < pl->cmd_count)
		{
			free_cmd(&pl->cmds[i]);
			i++;
		}
		free(pl->cmds);
	}
	free(pl);
}