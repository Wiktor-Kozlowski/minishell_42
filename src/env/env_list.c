/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:06:05 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/16 00:06:05 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_find(t_env *env, const char *key)
{
	size_t	klen;

	if (!key || !*key)
		return (NULL);
	klen = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, klen + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*env_get(t_env *env, const char *key)
{
	t_env	*n;

	n = env_find(env, key);
	if (!n)
		return (NULL);
	return (n->val);
}

int	env_unset(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;
	size_t	klen;

	if (!env || !*env || !key || !*key)
		return (1);
	klen = ft_strlen(key);
	prev = NULL;
	cur = *env;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, klen + 1) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->val);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

void	env_clear(t_env **env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->val);
		free(*env);
		*env = tmp;
	}
}
