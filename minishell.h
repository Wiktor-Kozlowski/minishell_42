/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:06:13 by wkozlows          #+#    #+#             */
/*   Updated: 2025/09/14 17:38:32 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* === Standard libraries === */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <ctype.h>
# include <limits.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>

/* === Readline === */
# include <readline/readline.h>
# include <readline/history.h>

/* === libft === */
# include "libft/libft.h"   /* wymagane: t_list, ft_* funkcje */

extern volatile sig_atomic_t	g_signal;

/* === Env list key=value === */
typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_sh
{
	t_env	*env;			// lista zmiennych środowiskowych
	int		last_status;	// ostatni kod wyjścia ($?)
	int		interactive;	// np. 1 = włączony prompt, 0 = off
}	t_sh;

/* === Token types === */
typedef enum e_token_type
{
	T_WORD,		/* słowo / argument */
	T_PIPE,		/* | */
	T_REDIR_IN,	/* < */
	T_REDIR_OUT,/* > */
	T_APPEND,	/* >> */
	T_HEREDOC	/* << */
}	t_token_type;

/* === Token === */
typedef struct s_token
{
	t_token_type	type;
	char			*value;  /* dla operatorów to np. ">>", "<", itp. */
	struct s_token	*next;
}	t_token;

/* === Redirections === */
typedef struct s_redir
{
	t_token_type	type;		// jaki rodzaj: <, >, >>, <<
	char			*target;	// nazwa pliku albo limiter (dla <<)
	int				fd;			// na jaki fd: zwykle 0 lub 1
	struct s_redir	*next;		// następne przekierowanie w tej komendzie
}	t_redir;

/* === Command === */
typedef struct s_cmd
{
	char	**argv;		// ["ls", "-l", NULL]
	t_redir	*redirs;	// lista przekierowań (> < >> <<)
	int		is_builtin;
}	t_cmd;

/* === Pipeline === */
typedef struct s_pipeline
{
	int		cmd_count;	// np. 3 dla A|B|C
	t_cmd	*cmds;		// tablica komend
}	t_pipeline;

/* === ASCII art intro === */
void	print_intro(void);

/* === Readline helpers === */
char	*generate_prompt(void);
char	*ft_readline(void);
void	run_line(t_sh *sh, char *line);

/* === Builtins === */
void	cmd_pwd(void);
int		cmd_echo(char **argv);
int		cmd_exit(void);

/* === Utils: whitespace === */
int		skipspace(const char *text, int i);

/* === Tokens / Lexer === */
t_token	*token_new(t_token_type type, const char *value);
t_token	*tokenize(const char *line);

/* === Lexer: pomocnicze funkcje === */
int		append_piece(char **buf, const char *piece);
int		read_quoted(const char *s, int i, char quote, char **buf);
int		read_word(const char *s, int i, char **out);

/* === External commands === */
int		ft_isspace(int c);

/* === Parser: główne funkcje === */
t_pipeline	*cr_pipeline(t_token *tokens);

/* === Parser: pomocnicze funkcje do pipeline === */
int			count_commands(t_token *tok);
int			count_args(t_token *tok);
int			is_builtin_name(const char *name);
int			is_redir_token(t_token_type type);
t_token		*next_cmd_start(t_token *token);

t_redir		*redir_new(t_token_type type, const char *target);
void		redir_add_back(t_redir **lst, t_redir *new_node);

/* === Shell state === */
int     sh_init(t_sh *sh, char **envp);
void    sh_destroy(t_sh *sh);

/* === Env === */
t_env	*env_from_envp(char **envp);
t_env	*env_find(t_env *env, const char *key);
char	*env_get(t_env *env, const char *key);
int		env_set(t_env **env, const char *key, const char *val);
int		env_unset(t_env **env, const char *key);
void	env_clear(t_env **env);

char	**env_to_envp(t_env *env);

int		is_valid_env_key(const char *s);

/* === Shell state === */
int		sh_init(t_sh *sh, char **envp);
void	sh_destroy(t_sh *sh);

/* === Executor === */
char	*find_executable(const char *cmd);
int		run_external(t_sh *sh, char **argv);
int		execute_pipeline(t_pipeline *pl, t_sh *sh);
//int		apply_redirs(t_redir *r);

void	exec_err2(const char *cmd, const char *msg);
int		exec_code_errno(int e);
int		status_to_code(int st);

/* === Path === */
int		has_slash(const char *s);
int		is_exec_file(const char *path);
char	*search_in_path(const char *cmd);

/* === Builtins (docelowo) === */
int		run_builtin(t_cmd *cmd, t_sh *sh);
int		is_stateful_builtin(const char *name);


/* === Free memory === */
void		free_pipeline(t_pipeline *pl);
void		free_tokens(t_token *head);
void		free_argv(char **argv);
void		free_envp(char **envp);

/* === Signals === */
void    install_parent_signals(void);
void	install_child_signals(void);

/* === Error === */
void		fatal_malloc_error(void);

#endif