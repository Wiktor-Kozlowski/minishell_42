#include "minishell.h"

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
		if (!ft_isdigit((unsigned char)s[i++]))
			return (0);
	return (1);
}

int	cmd_exit(t_sh *sh, char **args)
{
	int	code;

	ft_putendl_fd("exit", STDERR_FILENO);
	// easter egg
	if (args[1] && ft_strncmp(args[1], "secret", 7) == 0 && !args[2])
	{
		print_secret();
		sh_destroy(sh);
		exit(0);
	}
    if (args[1] && ft_strncmp(args[1], "monke", 6) == 0 && !args[2])
	{
		print_monke();
		sh_destroy(sh);
		exit(0);
	}
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (!args[1])
		code = sh->last_status;
	else if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		code = 255;
		sh_destroy(sh);
		exit(code);
	}
	else
		code = ft_atoi(args[1]) % 256;
	sh_destroy(sh);
	exit(code);
}