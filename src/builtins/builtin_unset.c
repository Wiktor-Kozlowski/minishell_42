#include "minishell.h"

int	cmd_unset(t_sh *sh, char **args){
    int x;
    char *key;

    x = 1;
    if (args[1] == NULL)
    {
        // printf("unset: not enough arguments ");
        return (0);
    }
    while (args[x] != NULL){
        key = args[x];
        if(!env_is_valid_key(key))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(key, STDERR_FILENO);
            ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
        }
        else 
            env_unset(&sh->env, key);
        
        x++;  
    }
    return (0);
}