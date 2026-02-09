#include "minishell.h"
#include <signal.h>

/* ================== */
/*  PROMPT + READLINE */
/* ================== */

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
char	*_ft_readline(void)
{
	char	*buffer;
	char	*prompt;

	prompt = generate_prompt();
	buffer = readline(prompt);
	free(prompt);
	return (buffer);
}

/* ================== */
/*  DEBUG: TOKENS     */
/* ================== */

static void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("[type=%d, value=\"%s\"]\n", tok->type,
			tok->value ? tok->value : "(null)");
		tok = tok->next;
	}
}

/* ================== */
/*  DEBUG: PIPELINE   */
/* ================== */

static void	print_redirs(t_redir *r)
{
	while (r)
	{
		printf("      redir: type=%d, fd=%d, target=\"%s\"\n",
			r->type, r->fd, r->target);
		r = r->next;
	}
}

static void	print_pipeline(t_pipeline *pl)
{
	int	i;
	int	j;

	if (!pl)
	{
		printf("pipeline = NULL\n");
		return ;
	}
	printf("PIPELINE: cmd_count = %d\n", pl->cmd_count);
	i = 0;
	while (i < pl->cmd_count)
	{
		printf("  CMD %d:\n", i);
		j = 0;
		while (pl->cmds[i].argv && pl->cmds[i].argv[j])
		{
			printf("    argv[%d] = \"%s\"\n", j, pl->cmds[i].argv[j]);
			j++;
		}
		printf("    is_builtin = %d\n", pl->cmds[i].is_builtin);
		print_redirs(pl->cmds[i].redirs);
		i++;
	}
}

/* ================== */
/*  MAIN LOOP         */
/* ================== */

int	main(void)
{
	char		*line;
	t_token		*tokens;
	t_pipeline	*pl;

	install_parent_signals();
	print_intro();
	while (1)
	{
		line = _ft_readline();
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		/* ------ LEXER ------ */
		tokens = tokenize(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		printf("=== TOKENS ===\n");
		print_tokens(tokens);

		/* ------ PARSER: PIPELINE ------ */
		pl = cr_pipeline(tokens);
		if (!pl)
			printf("cr_pipeline returned NULL (syntax error?)\n");
		else
		{
			printf("=== PIPELINE ===\n");
			print_pipeline(pl);
			free_pipeline(pl);
		}

		free_tokens(tokens);
		free(line);
	}
	return (EXIT_SUCCESS);
}
