/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:49:40 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/09 03:49:40 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_get_path(t_sh *sh, char **args)
{
    if (args[1] && args[2])
    {
        ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
        return (NULL);
    }
    else if (args[1] == NULL)
    {
        if (!env_get(sh->env, "HOME"))
        {
            ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
            return (NULL);
        }
        return (env_get(sh->env, "HOME"));
    }
    else if (ft_strncmp(args[1], "-", 2) == 0)
    {
        if (!env_get(sh->env, "OLDPWD"))
        {
            ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
            return (NULL);
        }
        return (env_get(sh->env, "OLDPWD"));
    }
    return (args[1]);
}

int cmd_cd(t_sh *sh, char **args){
    char *PATH;
    char *old_pwd;
    char buf[PATH_MAX];
    PATH = cd_get_path(sh, args);
    if (!PATH)
        return (1);
    old_pwd = env_get(sh->env, "PWD");
    if (chdir(PATH) == -1)
    {
    ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
    ft_putstr_fd(PATH, STDERR_FILENO);
    ft_putendl_fd(": No such file or directory", STDERR_FILENO);
    return (1);
    }
    env_set(&sh->env, "OLDPWD", old_pwd);
    getcwd(buf, PATH_MAX);
    env_set(&sh->env, "PWD", buf);
    return (0);
}
