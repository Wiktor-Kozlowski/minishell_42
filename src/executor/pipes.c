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

#include "include/minishell.h"

static int status_to_exitcode(int status)
{
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (1);
}

static void print_sig_msg_if_needed(int status)
{
    int sig;

    if (!WIFSIGNALED(status))
        return;
    sig = WTERMSIG(status);

    /* Bash: po SIGQUIT często wypisuje "Quit (core dumped)".
       Minimalnie możesz zrobić: */
    if (sig == SIGQUIT)
        write(2, "Quit (core dumped)\n", 19);
    /* Po SIGINT zwykle tylko nowa linia - u Ciebie handler już robi newline w prompt,
       a podczas wykonywania childy mają default, więc zazwyczaj wystarczy nic nie drukować. */
}

/*
** Zwraca exitcode (czyli to co ma trafić do sh->last_status).
** W pipeline: exitcode ostatniej komendy.
*/

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

static int	setup_child_fds(int i, int n, int (*p)[2])
{
	if (i > 0 && dup2(p[i - 1][0], STDIN_FILENO) < 0)
		return (1);
	if (i < n - 1 && dup2(p[i][1], STDOUT_FILENO) < 0)
		return (1);
	return (0);
}

static void	exec_child(t_cmd *cmd, int i, int n, int (*p)[2])
{
	install_child_signals();
	if (setup_child_fds(i, n, p))
		_exit(1);
	close_pipes(p, n - 1);
	if (apply_redirs(cmd->redirs))
		_exit(1);
	if (cmd->is_builtin)
	{
		/* TODO: run_builtin(cmd, sh) -> _exit(code); */
		_exit(0);
	}
	execve(find_executable(cmd->argv[0]), cmd->argv, NULL);
	_exit(127);
}

static int	wait_all(pid_t *pids, int n, pid_t last_pid)
{
	int		i;
	int		st;
	int		last_st;

	i = 0;
	last_st = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &st, 0) > 0 && pids[i] == last_pid)
			last_st = st;
		i++;
	}
	return (status_to_exitcode(last_st));
}

int	execute_pipeline(t_pipeline *pl, t_sh *sh)
{
	int		i;
	int		pn;
	int		p[1024][2];
	pid_t	pids[1024];
	pid_t	last_pid;

	i = 0;
	pn = pl->cmd_count - 1;
	while (i < pn && pipe(p[i]) == 0)
		i++;
	i = 0;
	while (i < pl->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			exec_child(&pl->cmds[i], i, pl->cmd_count, p);
		i++;
	}
	last_pid = pids[pl->cmd_count - 1];
	close_pipes(p, pn);
	sh->last_status = wait_all(pids, pl->cmd_count, last_pid);
	return (sh->last_status);
}
