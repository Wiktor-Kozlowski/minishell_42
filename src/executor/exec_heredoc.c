/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:00:00 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>

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
	free(pid);
	free(base);
	if (!tmp)
		return (free(num), NULL);
	path = ft_strjoin(tmp, num);
	free(tmp);
	free(num);
	return (path);
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

static int	close_heredoc_tmp(int fd, char *path, char *line, int status)
{
	free(line);
	close(fd);
	unlink(path);
	free(path);
	return (status);
}

static int	write_heredoc_line(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) < 0)
		return (1);
	if (write(fd, "\n", 1) < 0)
		return (1);
	return (0);
}

int	read_heredoc(t_redir *r)
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
			return (close_heredoc_tmp(fd, path, line,
					(exec_err2("heredoc", strerror(errno)), 1)));
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
