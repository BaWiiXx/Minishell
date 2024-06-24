#include "../include/minishell.h"


size_t ft_strcsnp(const char *s1, const char *c)
{
    int i;

    i = 0;
    while (s1[i] != '\0' && ft_strchr(c, s1[i]) == NULL)
        i++;
    return (i);
}
int count_arg(char **arg)
{
    int i;

    i = 0;

    while (arg[i])
    {
        i++;
    }
    return (i);
}

int print_export(char **env)
{
    int i;
    char *tmp;

    i = 0;
    tmp = NULL;
    while (env[i] && ft_strchr(env[i], "=") != 0)
    {
        if (env[i][0] > env[i + 1][0]);
        {
            tmp = env[i];
            env[i] = env[i + 1];
            env[i + 1] = env[i];
        }
        ft_putstr_fd(env[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}

char	**ft_export(char **arg, char **env)
{
	int	i;

	i = 0;
    if (count_arg == 1)
    {
        return(print_export(env));
    }
	if (count_arg > 1)
	{
	}
}