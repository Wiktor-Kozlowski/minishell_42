/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:50:49 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/09 03:50:49 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put2(int fd, const char *s)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	exec_err2(const char *cmd, const char *msg)
{
	put2(2, "minishell: ");
	put2(2, cmd);
	put2(2, ": ");
	put2(2, msg);
	put2(2, "\n");
}

int	exec_code_errno(int e)
{
	if (e == ENOENT)
		return (127);
	if (e == EACCES || e == EISDIR)
		return (126);
	return (126);
}

int	status_to_code(int st)
{
	if (WIFEXITED(st))
		return (WEXITSTATUS(st));
	if (WIFSIGNALED(st))
		return (128 + WTERMSIG(st));
	return (1);
}