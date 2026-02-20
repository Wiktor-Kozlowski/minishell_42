/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 00:38:37 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/20 00:50:20 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	child_exec(t_sh *sh, char **argv)
{
	char	*full;
	char	**envp;

	full = find_executable(argv[0]);
	if (!full)
		return (exec_err2(argv[0], "command not found"), exit(127));
	envp = env_to_envp(sh->env);
	execve(full, argv, envp);
	free(full);
	free_envp(envp);
	exec_err2(argv[0], strerror(errno));
	exit(exec_code_errno(errno));
}

int	run_external(t_sh *sh, char **argv)
{
	pid_t	pid;
	int		st;

	if (!argv || !argv[0])
		return (0);
	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), 1);
	if (pid == 0)
		child_exec(sh, argv);
	if (waitpid(pid, &st, 0) < 0)
		return (perror("minishell: waitpid"), 1);
	return (status_to_code(st));
}