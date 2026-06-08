/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wkozlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:00:00 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/07 22:22:14 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>

static int open_redir_fd(t_redir *r) {
	if (r->type == T_REDIR_IN)
		return (open(r->target, O_RDONLY));
	if (r->type == T_REDIR_OUT)
		return (open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (r->type == T_APPEND)
		return (open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static int dup_redir_fd(t_redir *r, int fd) {
	if (dup2(fd, r->fd) < 0) {
		close(fd);
		exec_err2(r->target, strerror(errno));
		return (1);
	}
	close(fd);
	return (0);
}

static char	*heredoc_tmp_path(int n)
{
	char	*pid;
	char	*num;
	char	*base;
	char	*tmp;
	char	*path;

	pid = ft_itoa(getpid());
	num = ft_itoa(n);
	if (!pid || !num)
		return (free(pid), free(num), NULL);
	base = ft_strjoin("/tmp/.minishell_heredoc_", pid);
	if (!base)
		return (free(pid), free(num), NULL);
	tmp = ft_strjoin(base, "_");
	if (!tmp)
		return (free(pid), free(num), free(base), NULL);
	path = ft_strjoin(tmp, num);
	free(pid);
	free(num);
	if (!path)
		return (free(base), free(tmp), NULL);
	free(base);
	free(tmp);
	return (path);
}

static int	close_heredoc_tmp(int fd, char *path, char *line, int status)
{
	free(line);
	close(fd);
	unlink(path);
	free(path);
	return (status);
}

static int	open_heredoc_tmp(char **path)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 1024)
	{
		*path = heredoc_tmp_path(i);
		if (!*path)
			return (-1);
		fd = open(*path, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
		if (fd >= 0)
			return (fd);
		free(*path);
		if (errno != EEXIST)
			return (-1);
		i++;
	}
	return (-1);
}

static int	write_heredoc_line(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) < 0)
		return (1);
	if (write(fd, "\n", 1) < 0)
		return (1);
	return (0);
}

static int	read_heredoc(t_redir *r)
{
	int		fd;
	char	*path;
	char	*line;

	path = NULL;
	fd = open_heredoc_tmp(&path);
	if (fd < 0)
		return (exec_err2("heredoc", strerror(errno)), 1);
	line = readline("> ");
	while (line)
	{
		if (g_signal == SIGINT)
			return (close_heredoc_tmp(fd, path, line, 130));
		if (ft_strncmp(line, r->target, ft_strlen(r->target) + 1) == 0)
			break ;
		if (write_heredoc_line(fd, line))
			return (free(line), close(fd), unlink(path), free(path),
				exec_err2("heredoc", strerror(errno)), 1);
		free(line);
		line = readline("> ");
	}
	if (g_signal == SIGINT)
		return (close_heredoc_tmp(fd, path, line, 130));
	free(line);
	close(fd);
	r->heredoc_fd = open(path, O_RDONLY);
	unlink(path);
	free(path);
	if (r->heredoc_fd < 0)
		return (exec_err2("heredoc", strerror(errno)), 1);
	return (0);
}

static int	dup_heredoc_fd(t_redir *r)
{
	if (r->heredoc_fd < 0)
		return (exec_err2("heredoc", "not prepared"), 1);
	if (dup2(r->heredoc_fd, r->fd) < 0)
		return (exec_err2("heredoc", strerror(errno)), 1);
	close(r->heredoc_fd);
	r->heredoc_fd = -1;
	return (0);
}

static int apply_one_redir(t_redir *r) {
	int fd;

	if (r->type == T_HEREDOC)
		return (dup_heredoc_fd(r));
	fd = open_redir_fd(r);
	if (fd < 0)
		return (exec_err2(r->target, strerror(errno)), 1);
	return (dup_redir_fd(r, fd));
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

int apply_redirs(t_redir *redirs) {
	while (redirs) {
		if (apply_one_redir(redirs))
			return (1);
		redirs = redirs->next;
	}
	return (0);
}
