/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:50:07 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_env(t_env *env)
{
	while (env)
	{
		if (env->val)
			printf("declare -x %s=\"%s\"\n", env->key, env->val);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

static void	export_set_one(t_sh *sh, char *arg)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	if (ft_strchr(arg, '='))
	{
		equal_sign = ft_strchr(arg, '=');
		key = ft_substr(arg, 0, equal_sign - arg);
		value = equal_sign + 1;
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (!env_is_valid_key(key))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
	else
		env_set(&sh->env, key, value);
	free(key);
}

int	cmd_export(t_sh *sh, char **args)
{
	int	x;

	x = 1;
	if (!args[1])
	{
		print_export_env(sh->env);
		return (0);
	}
	while (args[x])
	{
		export_set_one(sh, args[x]);
		x++;
	}
	return (0);
}
