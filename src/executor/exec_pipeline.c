/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:40:26 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_run(t_pipeline *pl, t_sh *sh, int i, int (*p)[2])
{
	char	**argv;
	char	*full;
	char	**envp;

	argv = pl->cmds[i].argv;
	install_child_signals();
	if (i > 0 && dup2(p[i - 1][0], STDIN_FILENO) < 0)
		exit(1);
	if (i < pl->cmd_count - 1 && dup2(p[i][1], STDOUT_FILENO) < 0)
		exit(1);
	close_pipes(p, pl->cmd_count - 1);
	if (apply_redirs(pl->cmds[i].redirs))
		exit(1);
	if (!argv[0])
		exit(0);
	if (pl->cmds[i].is_builtin)
		exit(run_builtin(&pl->cmds[i], sh));
	full = find_executable(sh->env, argv[0]);
	if (!full && !has_slash(argv[0]))
		return (exec_err2(argv[0], "command not found"), exit(127));
	if (!full)
		exec_err_exit(argv[0], errno);
	envp = env_to_envp(sh->env);
	execve(full, argv, envp);
	exec_err_exit(argv[0], errno);
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

static int	run_heredocs(t_pipeline *pl, t_sh *sh)
{
	int	st;

	st = prepare_heredocs(pl);
	if (st == 130)
		g_signal = 0;
	if (st)
		return (sh->last_status = st, 1);
	return (0);
}

static int	setup_exec(int pn, int n, int (**pp)[2], pid_t **ppids)
{
	int	i;

	*pp = malloc(sizeof(int [2]) * pn);
	*ppids = malloc(sizeof(pid_t) * n);
	if ((!*pp && pn > 0) || !*ppids)
		return (free(*pp), free(*ppids), 1);
	i = 0;
	while (i < pn && pipe((*pp)[i]) == 0)
		i++;
	return (0);
}

int	execute_pipeline(t_pipeline *pl, t_sh *sh)
{
	int		i;
	int		pn;
	int		(*p)[2];
	pid_t	*pids;

	if (run_heredocs(pl, sh))
		return (sh->last_status);
	if (pl->cmd_count == 1 && pl->cmds[0].is_builtin
		&& is_stateful_builtin(pl->cmds[0].argv[0]))
		return (sh->last_status = run_builtin(&pl->cmds[0], sh));
	pn = pl->cmd_count - 1;
	if (setup_exec(pn, pl->cmd_count, &p, &pids))
		return (1);
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
