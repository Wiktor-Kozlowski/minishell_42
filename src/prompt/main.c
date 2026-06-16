/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:57:31 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	handle_eof(void)
{
	write(1, "exit\n", 5);
}

static void	shell_loop(t_sh *sh)
{
	char	*line;

	while (1)
	{
		g_signal = 0;
		line = ft_readline();
		if (!line)
		{
			if (g_signal == SIGINT)
				continue ;
			handle_eof();
			break ;
		}
		if (*line)
			run_line(sh, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;

	(void)argc;
	(void)argv;
	if (!sh_init(&sh, envp))
		return (EXIT_FAILURE);
	print_intro();
	install_parent_signals();
	shell_loop(&sh);
	sh_destroy(&sh);
	return (sh.last_status);
}
