/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:45:51 by wkozlows          #+#    #+#             */
/*   Updated: 2026/02/16 01:45:51 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Buduje dynamiczny prompt: lewa strona to wynik getcwd(), a prawa statyczny
** sufiks z nazwa powloki. W razie bledu pobierania katalogu przechodzimy na
** prosty "$> " aby nadal umozliwic interakcje.
*/
char	*generate_prompt(void)
{
	char		path[PATH_MAX];
	char		*prompt;
	const char	*name = " $piwkomuszla$> ";

	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("getcwd");
		return (ft_strdup("$> "));
	}
	prompt = ft_strjoin(path, name);
	if (!prompt)
		fatal_malloc_error();
	return (prompt);
}

/*
** Owijka na readline(): kazde odczytanie linii ma swiezo wygenerowany prompt,
** dzieki czemu zmiana katalogu widoczna jest od razu.
*/
char	*ft_readline(void)
{
	char	*buffer;
	char	*prompt;

	prompt = generate_prompt();
	buffer = readline(prompt);
	free(prompt);
	return (buffer);
}

void	run_line(t_sh *sh, char *line)
{
	t_token		*tokens;
	t_pipeline	*pl;

	if (*line)
		add_history(line);
	tokens = tokenize(line);
	if (!tokens)
		return ;
	pl = cr_pipeline(tokens);
	if (pl)
	{
		execute_pipeline(pl, sh);
		free_pipeline(pl);
	}
	free_tokens(tokens);
}
