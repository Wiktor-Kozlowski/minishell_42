/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:25:48 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/16 00:25:48 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*sh_env_new(const char *key, const char *val)
{
	t_env	*n;

	n = (t_env *)malloc(sizeof(*n));
	if (!n)
		fatal_malloc_error();
	n->key = ft_strdup(key);
	if (!n->key)
		fatal_malloc_error();
	n->val = NULL;
	if (val)
	{
		n->val = ft_strdup(val);
		if (!n->val)
			fatal_malloc_error();
	}
	n->next = NULL;
	return (n);
}

static void	sh_env_add_back(t_env **env, t_env *new_node)
{
	t_env	*cur;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	cur = *env;
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;
}

static void	sh_env_update_value(t_env *node, const char *val)
{
	char	*new_val;

	new_val = NULL;
	if (val)
	{
		new_val = ft_strdup(val);
		if (!new_val)
			fatal_malloc_error();
	}
	free(node->val);
	node->val = new_val;
}

int	env_set(t_env **env, const char *key, const char *val)
{
	t_env	*node;

	if (!env || !key || !*key)
		return (1);
	node = env_find(*env, key);
	if (node)
		return (sh_env_update_value(node, val), 0);
	sh_env_add_back(env, sh_env_new(key, val));
	return (0);
}
