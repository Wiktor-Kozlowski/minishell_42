/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 00:33:07 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/20 00:53:25 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	has_slash(const char *s)
{
	while (s && *s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}

int	is_exec_file(const char *path)
{
	struct stat	st;

	if (!path || !*path)
		return (0);
	if (stat(path, &st) != 0)
		return (0);
	if (S_ISDIR(st.st_mode))
	{
		errno = EISDIR;
		return (0);
	}
	if (!S_ISREG(st.st_mode))
	{
		errno = EACCES;
		return (0);
	}
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

char	*path_join(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

void	free_split(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*search_in_path(const char *cmd)
{
	char	*path;
	char	**dirs;
	char	*full;
	size_t	i;

	path = getenv("PATH");
	if (!path || !*path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full = path_join(dirs[i++], cmd);
		if (full && is_exec_file(full))
			return (free_split(dirs), full);
		free(full);
	}
	return (free_split(dirs), NULL);
}