/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:40:26 by wkozlows          #+#    #+#             */
/*   Updated: 2025/11/13 22:40:26 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	close_pipes(int (*p)[2], int n)
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

static int	setup_fds(int i, int n, int (*p)[2])
{
	if (i > 0 && dup2(p[i - 1][0], STDIN_FILENO) < 0)
		return (1);
	if (i < n - 1 && dup2(p[i][1], STDOUT_FILENO) < 0)
		return (1);
	return (0);
}

static void	child_run(t_pipeline *pl, t_sh *sh, int i, int (*p)[2])
{
	char	*full;
	char	**envp;

	install_child_signals();
	if (setup_fds(i, pl->cmd_count, p))
		exit(1);
	close_pipes(p, pl->cmd_count - 1);
//	if (apply_redirs(pl->cmds[i].redirs))
//		exit(1);
	if (pl->cmds[i].is_builtin)
		{
			write(1, "builtins not implemented yet. :(\n", 33);
			exit(1);
		}
//		exit(run_builtin(&pl->cmds[i], sh));
	full = find_executable(pl->cmds[i].argv[0]);
	if (!full)
		return (exec_err2(pl->cmds[i].argv[0], "command not found"), exit(127));
	envp = env_to_envp(sh->env);
	execve(full, pl->cmds[i].argv, envp);
	free(full);
	free_envp(envp);
	exec_err2(pl->cmds[i].argv[0], strerror(errno));
	exit(126);
}

static int	wait_all(pid_t *pids, int n, pid_t last)
{
	int	i;
	int	st;
	int	last_st;

	i = 0;
	last_st = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &st, 0) > 0 && pids[i] == last)
			last_st = st;
		i++;
	}
	if (WIFSIGNALED(last_st) && WTERMSIG(last_st) == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	return (status_to_code(last_st));
}

int	execute_pipeline(t_pipeline *pl, t_sh *sh)
{
	int		i;
	int		pn;
	int		(*p)[2];
	pid_t	*pids;

	pn = pl->cmd_count - 1;
	p = malloc(sizeof(int [2]) * pn);
	pids = malloc(sizeof(pid_t) * pl->cmd_count);
	if ((!p && pn > 0) || !pids)
		return (free(p), free(pids), 1);
	i = 0;
	while (i < pn && pipe(p[i]) == 0)
		i++;
	i = 0;
	while (i < pl->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			child_run(pl, sh, i, p);
		i++;
	}
	close_pipes(p, pn);
	sh->last_status = wait_all(pids, pl->cmd_count, pids[pl->cmd_count - 1]);
	return (free(p), free(pids), sh->last_status);
}