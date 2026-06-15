/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sh_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:56:59 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/15 20:56:59 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sh_init(t_sh *sh, char **envp)
{
	if (!sh)
		return (0);
	sh->env = env_from_envp(envp);
	sh->last_status = 0;
	sh->interactive = isatty(STDIN_FILENO);
	return (1);
}

void	sh_destroy(t_sh *sh)
{
	if (!sh)
		return ;
	env_clear(&sh->env);
}
