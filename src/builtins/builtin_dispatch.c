/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 00:00:00 by wkozlows          #+#    #+#             */
/*   Updated: 2026/03/21 19:01:48 by marvin           ###   ########.fr       */
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
	if (streq(cmd->argv[0], "cd")
		|| streq(cmd->argv[0], "unset")
		|| streq(cmd->argv[0], "env"))
	{
		ft_putstr_fd("minishell: builtin not implemented yet\n", 2);
		return (1);
	}
	return (1);
}
