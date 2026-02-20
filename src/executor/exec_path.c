/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 00:35:24 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/20 00:36:44 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_executable(const char *cmd)
{
	if (!cmd || !*cmd)
		return (NULL);
	if (has_slash(cmd))
	{
		if (is_exec_file(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (search_in_path(cmd));
}