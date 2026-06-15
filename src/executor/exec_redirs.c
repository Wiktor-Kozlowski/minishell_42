/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:00:00 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	open_redir_fd(t_redir *r)
{
	if (r->type == T_REDIR_IN)
		return (open(r->target, O_RDONLY));
	if (r->type == T_REDIR_OUT)
		return (open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (r->type == T_APPEND)
		return (open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static int	dup_redir_fd(t_redir *r, int fd)
{
	if (dup2(fd, r->fd) < 0)
	{
		close(fd);
		exec_err2(r->target, strerror(errno));
		return (1);
	}
	close(fd);
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

static int	apply_one_redir(t_redir *r)
{
	int	fd;

	if (r->type == T_HEREDOC)
		return (dup_heredoc_fd(r));
	fd = open_redir_fd(r);
	if (fd < 0)
		return (exec_err2(r->target, strerror(errno)), 1);
	return (dup_redir_fd(r, fd));
}

int	apply_redirs(t_redir *redirs)
{
	while (redirs)
	{
		if (apply_one_redir(redirs))
			return (1);
		redirs = redirs->next;
	}
	return (0);
}
