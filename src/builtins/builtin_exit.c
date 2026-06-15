/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:49:47 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
		if (!ft_isdigit((unsigned char)s[i++]))
			return (0);
	return (1);
}

static void	exit_easter_egg(t_sh *sh, char **args)
{
	if (args[1] && ft_strncmp(args[1], "secret", 7) == 0 && !args[2])
	{
		print_secret();
		sh_destroy(sh);
		exit(0);
	}
	if (args[1] && ft_strncmp(args[1], "monke", 6) == 0 && !args[2])
	{
		print_monke();
		sh_destroy(sh);
		exit(0);
	}
}

static int	exit_get_code(t_sh *sh, char **args)
{
	if (!args[1])
		return (sh->last_status);
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		sh_destroy(sh);
		exit(255);
	}
	return (ft_atoi(args[1]) % 256);
}

int	cmd_exit(t_sh *sh, char **args)
{
	int	code;

	exit_easter_egg(sh, args);
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	code = exit_get_code(sh, args);
	sh_destroy(sh);
	exit(code);
}
