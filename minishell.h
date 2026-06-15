/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:06:13 by wkozlows          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <ctype.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"

extern volatile sig_atomic_t	g_signal;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_sh
{
	t_env	*env;
	int		last_status;
	int		interactive;
}	t_sh;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	int				fd;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	t_redir	*redirs;
	int		is_builtin;
}	t_cmd;

typedef struct s_pipeline
{
	int		cmd_count;
	t_cmd	*cmds;
}	t_pipeline;

/* === ASCII art intro === */
void		print_intro(void);

/* === Readline helpers === */
char		*generate_prompt(void);
char		*ft_readline(void);
void		run_line(t_sh *sh, char *line);

/* === Builtins === */
int			cmd_pwd(t_sh *sh);
int			cmd_echo(char **argv);
int			cmd_exit(t_sh *sh, char **args);
int			cmd_export(t_sh *sh, char **args);
int			cmd_unset(t_sh *sh, char **args);
int			cmd_cd(t_sh *sh, char **args);
int			cmd_env(t_env *env, char **args);

/* === Easter eggs === */
void		print_secret(void);
void		print_monke(void);

/* === Utils: whitespace === */
int			skipspace(const char *text, int i);
int			ft_isspace(int c);

/* === Tokens / Lexer === */
t_token		*tokenizer(const char *line, t_sh *sh);
t_token		*token_new(t_token_type type, const char *value);

/* === Lexer helpers === */
int			append_piece(char **buf, const char *piece);
int			read_word(const char *s, int i, char **out, t_sh *sh);
int			expand_dollar(const char *s, int *i, char **buf, t_sh *sh);
int			is_var_start(char c);
int			is_var_char(char c);
int			append_char(char **buf, char c);

/* === Parser === */
t_pipeline	*cr_pipeline(t_token *tokens);
int			apply_redirs(t_redir *redirs);
int			read_heredoc(t_redir *r);
int			prepare_heredocs(t_pipeline *pl);

/* === Parser helpers === */
int			count_commands(t_token *tok);
int			count_args(t_token *tok);
int			is_builtin_name(const char *name);
int			is_redir_token(t_token_type type);
t_token		*next_cmd_start(t_token *token);
t_redir		*redir_new(t_token_type type, const char *target);
void		redir_add_back(t_redir **lst, t_redir *new_node);

/* === Shell state === */
int			sh_init(t_sh *sh, char **envp);
void		sh_destroy(t_sh *sh);

/* === Env === */
t_env		*env_from_envp(char **envp);
t_env		*env_find(t_env *env, const char *key);
char		*env_get(t_env *env, const char *key);
int			env_set(t_env **env, const char *key, const char *val);
int			env_unset(t_env **env, const char *key);
void		env_clear(t_env **env);
char		**env_to_envp(t_env *env);
int			env_is_valid_key(const char *s);
void		free_envp(char **envp);

/* === Executor === */
char		*find_executable(t_env *env, const char *cmd);
int			run_external(t_sh *sh, char **argv);
int			execute_pipeline(t_pipeline *pl, t_sh *sh);
void		close_pipes(int (*p)[2], int n);
void		exec_err2(const char *cmd, const char *msg);
int			exec_code_errno(int e);
int			status_to_code(int st);

/* === Path === */
int			has_slash(const char *s);
int			is_exec_file(const char *path);
char		*search_in_path(t_env *env, const char *cmd);

/* === Builtins router === */
int			run_builtin(t_cmd *cmd, t_sh *sh);
int			is_stateful_builtin(const char *name);

/* === Free memory === */
void		free_pipeline(t_pipeline *pl);
void		free_tokens(t_token *head);
void		free_argv(char **argv);

/* === Signals === */
void		install_parent_signals(void);
void		install_child_signals(void);

/* === Error === */
void		fatal_malloc_error(void);

#endif
