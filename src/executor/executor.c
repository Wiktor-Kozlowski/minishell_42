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

#include "include/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

static int  has_slash(const char *s)
{
    while (s && *s)
    {
        if (*s == '/')
            return (1);
        s++;
    }
    return (0);
}

static int  is_executable_file(const char *path)
{
    struct stat st;

    if (!path)
        return (0);
    if (stat(path, &st) != 0)
        return (0);
    if (!S_ISREG(st.st_mode))
    {
        errno = (S_ISDIR(st.st_mode) ? EISDIR : EACCES);
        return (0);
    }
    if (access(path, X_OK) != 0)
        return (0);
    return (1);
}

static char *path_join(const char *dir, const char *cmd)
{
    char    *tmp;
    char    *full;

    if (!dir || !cmd)
        return (NULL);
    tmp = ft_strjoin(dir, "/");
    if (!tmp)
        return (NULL);
    full = ft_strjoin(tmp, cmd);
    free(tmp);
    return (full);
}

static void free_split(char **arr)
{
    size_t  i;

    if (!arr)
        return ;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

static char *search_in_path(const char *cmd)
{
    char    *path;
    char    **dirs;
    char    *full;
    size_t  i;

    path = getenv("PATH");
    if (!path || !*path)
        return (NULL);
    dirs = ft_split(path, ':');
    if (!dirs)
        return (NULL);
    i = 0;
    full = NULL;
    while (dirs[i])
    {
        full = path_join(dirs[i], cmd);
        if (!full)
            break ;
        if (is_executable_file(full))
        {
            free_split(dirs);
            return (full);
        }
        free(full);
        full = NULL;
        i++;
    }
    free_split(dirs);
    return (NULL);
}

char    *find_executable(const char *cmd)
{
    if (!cmd || !*cmd)
        return (NULL);
    if (has_slash(cmd))
    {
        if (is_executable_file(cmd))
            return (ft_strdup(cmd));
        return (NULL);
    }
    return (search_in_path(cmd));
}

static void exec_child(char **argv, char *full)
{
    extern char **environ;

    if (!full)
    {
        fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
        _exit(127);
    }
    execve(full, argv, environ);
    if (errno == EACCES || errno == EISDIR)
    {
        fprintf(stderr, "minishell: %s: %s\n", argv[0], strerror(errno));
        _exit(126);
    }
    else if (errno == ENOENT)
    {
        fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
        _exit(127);
    }
    fprintf(stderr, "minishell: %s: %s\n", argv[0], strerror(errno));
    _exit(126);
}

int run_external(char **argv)
{
    pid_t   pid;
    int     status;
    char    *full;

    if (!argv || !argv[0])
        return (0);
    full = find_executable(argv[0]);
    pid = fork();
    if (pid < 0)
    {
        perror("minishell: fork");
        free(full);
        return (1);
    }
    if (pid == 0)
        exec_child(argv, full);
    free(full);
    if (waitpid(pid, &status, 0) < 0)
    {
        perror("minishell: waitpid");
        return (1);
    }
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (1);
}
