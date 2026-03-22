/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:00:00 by wkozlows          #+#    #+#             */
/*   Updated: 2026/03/22 12:12:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	streq(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	return (ft_strncmp(a, b, ft_strlen(b) + 1) == 0);
}

int	is_stateful_builtin(const char *name)
{
	if (!name)
		return (0);
	return (streq(name, "cd") || streq(name, "export")
		|| streq(name, "unset") || streq(name, "exit"));
}

int	run_builtin(t_cmd *cmd, t_sh *sh)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	/* Dispatch builtins and return their exit status. */
	if (streq(cmd->argv[0], "echo"))
		return (cmd_echo(cmd->argv));
	if (streq(cmd->argv[0], "pwd"))
		return (cmd_pwd(sh));
	if (streq(cmd->argv[0], "exit"))
		return (cmd_exit(sh, cmd->argv));
	if (streq(cmd->argv[0], "export"))
		return (cmd_export(sh, cmd->argv));
	if (streq(cmd->argv[0], "env"))
		return (cmd_env(sh->env, cmd->argv));
	if (streq(cmd->argv[0], "unset"))
		return (cmd_unset(sh, cmd->argv));
	if (streq(cmd->argv[0], "cd"))
		return (cmd_cd(sh, cmd->argv));
	return (1);
}
