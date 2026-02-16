/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:31:29 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/16 00:31:29 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*sh_join_key_val(const char *key, const char *val)
{
	size_t	klen;
	size_t	vlen;
	char	*s;

	klen = ft_strlen(key);
	vlen = 0;
	if (val)
		vlen = ft_strlen(val);
	s = (char *)malloc(klen + 1 + vlen + 1);
	if (!s)
		fatal_malloc_error();
	ft_memcpy(s, key, klen);
	s[klen] = '=';
	if (val)
		ft_memcpy(s + klen + 1, val, vlen);
	s[klen + 1 + vlen] = '\0';
	return (s);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	size_t	n;
	size_t	i;
	t_env	*tmp;

	n = 0;
	tmp = env;
	while (tmp && ++n)
		tmp = tmp->next;
	envp = (char **)malloc(sizeof(char *) * (n + 1));
	if (!envp)
		fatal_malloc_error();
	i = 0;
	while (env)
	{
		envp[i++] = sh_join_key_val(env->key, env->val);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_envp(char **envp)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

int	env_is_valid_key(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!(ft_isalpha((unsigned char)s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i])
		if (!(ft_isalnum((unsigned char)s[i++]) || s[i - 1] == '_'))
			return (0);
	return (1);
}
