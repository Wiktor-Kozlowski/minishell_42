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

static int heredoc_to_stdin(const char *delim) {
	int p[2];
	char *line;

	if (pipe(p) < 0)
		return (exec_err2("heredoc", strerror(errno)), 1);
	line = readline("> ");
	while (line) {
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
			break;
		write(p[1], line, ft_strlen(line));
		write(p[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(p[1]);
	if (dup2(p[0], STDIN_FILENO) < 0)
		return (close(p[0]), exec_err2("heredoc", strerror(errno)), 1);
	close(p[0]);
	return (0);
}

static int apply_one_redir(t_redir *r) {
	int fd;

	if (r->type == T_HEREDOC)
		return (heredoc_to_stdin(r->target));
	fd = open_redir_fd(r);
	if (fd < 0)
		return (exec_err2(r->target, strerror(errno)), 1);
	return (dup_redir_fd(r, fd));
}

int apply_redirs(t_redir *redirs) {
	while (redirs) {
		if (apply_one_redir(redirs))
			return (1);
		redirs = redirs->next;
	}
	return (0);
}
