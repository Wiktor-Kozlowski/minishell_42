/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 00:38:37 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	close_pipes(int (*p)[2], int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(p[i][0]);
		close(p[i][1]);
		i++;
	}
}

static void	child_exec(t_sh *sh, char **argv)
{
	char	*full;
	char	**envp;

	full = find_executable(sh->env, argv[0]);
	if (!full)
	{
		if (!has_slash(argv[0]))
			return (exec_err2(argv[0], "command not found"), exit(127));
		return (exec_err2(argv[0], strerror(errno)), exit(exec_code_errno(errno)));
	}
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

int	prepare_heredocs(t_pipeline *pl)
{
	int		i;
	int		status;
	t_redir	*r;

	i = 0;
	while (i < pl->cmd_count)
	{
		r = pl->cmds[i].redirs;
		while (r)
		{
			if (r->type == T_HEREDOC)
			{
				status = read_heredoc(r);
				if (status)
					return (status);
			}
			r = r->next;
		}
		i++;
	}
	return (0);
}
