/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wkozlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 21:20:34 by wkozlows          #+#    #+#             */
/*   Updated: 2026/03/24 22:51:55 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_exit_status(char **buf, t_sh *sh)
{
	char*status;
	int		ret;

	status = ft_itoa(sh->last_status);
	if (!status)
		return (-1);
	ret = append_piece(buf, status);
	free(status);
	return (ret);
}

static int	expand_named_var(const char *s, int *i, char **buf, t_sh *sh)
{
	int		start;
	char	*name;
	char	*value;

	start = *i;
	while (s[*i] && is_var_char(s[*i]))
		(*i)++;
	name = ft_substr(s, start, *i - start);
	if (!name)
		return (-1);
	value = env_get(sh->env, name);
	free(name);
	if (!value)
		return (0);
	return (append_piece(buf, value));
}

int	expand_dollar(const char *s, int *i, char **buf, t_sh *sh)
{
	int	j;

	j = *i + 1;
	if (s[j] == '?')
	{
		*i = j + 1;
		return (expand_exit_status(buf, sh));
	}
	if (ft_isdigit((unsigned char)s[j]))
	{
		*i = j + 1;
		return (0);
	}
	if (!is_var_start(s[j]))
	{
		(*i)++;
		return (append_char(buf, '$'));
	}
	*i = j;
	return (expand_named_var(s, i, buf, sh));
}
