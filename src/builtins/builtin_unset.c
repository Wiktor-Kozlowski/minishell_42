#include "minishell.h"

int	cmd_unset(t_sh *sh, char **args){
    int x;
    char *key;
    char *equal_sign;
    char *value;

    x = 1;
    if (args[1] == NULL)
    {
        print_export_env(sh->env);
        return (0);
    }
    while (args[x] != NULL){
        if (args[x] != NULL && ft_strchr(args[x], '=')){
            equal_sign  = ft_strchr(args[x], '=');
            key = ft_substr(args[x], 0, equal_sign - args[x]);
            value = equal_sign + 1;
        }
        if (args[x] != NULL && !ft_strchr(args[x], '=')){
                key = ft_strdup(args[x]);
                value = NULL;
        }
        if(!env_is_valid_key(key)){
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(key, STDERR_FILENO);
            ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
        }
        else
            env_set(&sh->env, key, value);
        free(key);
         x++;  
    }
    return (0);
}