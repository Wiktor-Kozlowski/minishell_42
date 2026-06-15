/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:49:37 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_has_invalid_args(char **args)
{
	if (!args)
		return (0);
	if (args[1] != NULL)
	{
		ft_putendl_fd("minishell: env: too many arguments", 2);
		return (1);
	}
	return (0);
}

int	cmd_env(t_env *env, char **args)
{
	if (env_has_invalid_args(args))
		return (1);
	while (env)
	{
		if (env->val)
			printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
	return (0);
}