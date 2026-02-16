/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 03:49:54 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/09 03:49:54 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* echo builtin:
   - supports multiple -n flags (e.g., -n -n)
   - prints joined args separated by spaces
*/
int cmd_echo(char **argv)
{
    int i;
    int no_newline;
    int j;

    i = 1;
    no_newline = 0;
    while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
    {
        j = 2;
        while (argv[i][j] == 'n')
            j++;
        if (argv[i][j] != '\0')
            break ;
        no_newline = 1;
        i++;
    }
    while (argv[i])
    {
        fputs(argv[i], stdout);
        if (argv[i + 1])
            fputc(' ', stdout);
        i++;
    }
    if (!no_newline)
        fputc('\n', stdout);
    return (0);
}
