NAME            := minishell
CC              := cc
CFLAGS          := -Wall -Wextra -Werror -MMD -MP
CPPFLAGS        := -I. -Iinclude -Ilibft

BREW_READLINE   := $(shell brew --prefix readline 2>/dev/null)
ifeq ($(BREW_READLINE),)
READLINE_INC    ?=
READLINE_LIB    ?= -lreadline
else
READLINE_INC    ?= -I$(BREW_READLINE)/include
READLINE_LIB    ?= -L$(BREW_READLINE)/lib -lreadline
endif

LIBFT_DIR       := libft
LIBFT           := $(LIBFT_DIR)/libft.a

SRC             := \
	src/prompt/main.c \
	src/prompt/loop.c  \
	src/builtins/builtin_cd.c \
	src/builtins/builtin_echo.c \
	src/builtins/builtin_env.c \
	src/builtins/builtin_exit.c \
	src/builtins/builtin_export.c \
	src/builtins/builtin_pwd.c \
	src/builtins/builtin_unset.c \
	src/env/env_init.c \
	src/env/env_list.c \
	src/env/env_utils.c \
	src/env/env_set.c \
	src/env/env_sh_state.c \
	src/executor/executor.c \
	src/executor/pipes.c \
	src/executor/process.c \
	src/executor/redirections.c \
	src/lexer/lexer.c \
	src/lexer/lexer_utils.c \
	src/lexer/tokenizer.c \
	src/parser/ast_builder.c \
	src/parser/p_pipeline.c \
	src/parser/p_redir.c \
	src/parser/p_utils.c \
	src/signals/signals_child.c \
	src/signals/signals_parent.c \
	src/utils/free_utils.c \
	src/utils/ft_error.c \
	src/utils/ft_split_custom.c \
	src/utils/ft_strjoin_free.c \
	src/utils/utils.c

OBJ_DIR         := build
OBJ             := $(SRC:.c=.o)
OBJ             := $(addprefix $(OBJ_DIR)/,$(OBJ))
DEP             := $(OBJ:.o=.d)

.PHONY: all clean fclean re libft

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE_LIB) -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(READLINE_INC) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all

-include $(DEP)
