/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:57:31 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/15 20:57:31 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <signal.h>

/* ================== */
/*  DEBUG: TOKENS     */
/* ================== */
/*
static void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("[type=%d, value=\"%s\"]\n", tok->type,
			tok->value ? tok->value : "(null)");
		tok = tok->next;
	}
}
*/
/* ================== */
/*  DEBUG: PIPELINE   */
/* ================== */
/*
static void	print_redirs(t_redir *r)
{
	while (r)
	{
		printf("      redir: type=%d, fd=%d, target=\"%s\"\n",
			r->type, r->fd, r->target);
		r = r->next;
	}
}

static void	print_pipeline(t_pipeline *pl)
{
	int	i;
	int	j;

	if (!pl)
	{
		printf("pipeline = NULL\n");
		return ;
	}
	printf("PIPELINE: cmd_count = %d\n", pl->cmd_count);
	i = 0;
	while (i < pl->cmd_count)
	{
		printf("  CMD %d:\n", i);
		j = 0;
		while (pl->cmds[i].argv && pl->cmds[i].argv[j])
		{
			printf("    argv[%d] = \"%s\"\n", j, pl->cmds[i].argv[j]);
			j++;
		}
		printf("    is_builtin = %d\n", pl->cmds[i].is_builtin);
		print_redirs(pl->cmds[i].redirs);
		i++;
	}
}
*/

/* ================== */
/*  MAIN LOOP         */
/* ================== */

static void	handle_eof(void)
{
	write(1, "exit\n", 5);
}


static int	handle_prompt_sigint(t_sh *sh)
{
	if (g_signal != SIGINT)
		return (0);
	g_signal = 0;
	sh->last_status = 130;
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;
	char	*line;

	(void)argc;
	(void)argv;
	if (!sh_init(&sh, envp))
		return (EXIT_FAILURE);
	print_intro();
	install_parent_signals();
	while (1)
	{
		line = ft_readline();
		if (!line)
		{
			handle_eof();
			break ;
		}
		if (handle_prompt_sigint(&sh))
		{
			free(line);
			continue ;
		}
		if (*line)
			run_line(&sh, line);
		free(line);
	}
	sh_destroy(&sh);
	return (EXIT_SUCCESS);
}