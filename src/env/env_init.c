/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:54:01 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/15 20:54:01 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*sh_dup_key(const char *s, size_t len)
{
	char	*key;

	key = (char *)malloc(len + 1);
	if (!key)
		fatal_malloc_error();
	ft_memcpy(key, s, len);
	key[len] = '\0';
	return (key);
}

static void	sh_env_push_entry(t_env **env, const char *entry)
{
	char	*eq;
	char	*key;

	if (!entry || !*entry)
		return ;
	eq = ft_strchr(entry, '=');
	if (!eq)
	{
		(void)env_set(env, entry, NULL);
		return ;
	}
	if (eq == (char *)entry)
		return ;
	key = sh_dup_key(entry, (size_t)(eq - entry));
	(void)env_set(env, key, eq + 1);
	free(key);
}

t_env	*env_from_envp(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		sh_env_push_entry(&env, envp[i]);
		i++;
	}
	return (env);
}
