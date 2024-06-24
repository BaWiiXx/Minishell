/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:36:08 by bdany             #+#    #+#             */
/*   Updated: 2024/06/21 19:32:50 by baptiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_pwd(void);

void ft_puterr_endl(char *str)
{
	ft_putendl_fd(str, 2);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		i++;
	}
	return (i);
}

char	**ft_str_tab_dup(char **tab_tmp)
{
	int		i;
	char	**tab;

	i = 0;
	while (tab_tmp[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (tab_tmp[i])
	{
		tab[i] = ft_strdup(tab_tmp[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_getenv(char *to_find, char **env)
{
	int	i;
	int	len;

	i = 0;
	to_find = ft_strjoin(to_find, "=");
	len = ft_strlen(to_find);
	while (env[i] && !ft_strnstr(env[i], to_find, len))
		i++;
	free(to_find);
	if (env[i])
		return (env[i] + len);
	return (NULL);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	if(count_arg(env) > 1)
	{
		ft_puterr_endl("bash: env: too many arguments");
		return (1);
	}
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	ft_echo(char **arg)
{
	int	i;
	int	n;

	i = 2;
	n = 0;
	if (count_arg(arg) > 1)
	{
		while (arg[i] && ft_strcmp(arg[i], "-n") == 0)
		{
			n = 1;
			i++;
		}
		while (arg[i] && arg[i + 1])
		{
			ft_putstr_fd(arg[i], STDOUT_FILENO);
			ft_putstr_fd(" ", 1);
			i++;
		}
		if (arg[i])
			ft_putstr_fd(arg[i], STDOUT_FILENO);
	}
	if (n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	ft_cd(char **arg, char **env)
{
	char	*home;

	if (count_arg(arg) == 2)
	{
		if (chdir(arg[1]))
			printf("bash: cd: %s: No such file or directory\n", arg[1]);
	}
	else if (count_arg(arg) == 1)
	{
		home = ft_getenv("HOME", env);
		if (!home)
			printf("bash: cd: HOME not set\n");
		else
			chdir(home);
	}
	else
		printf("bash: cd: too many arguments\n");
	return (0);
}
char	**ft_unset(char *to_find, char **env_tmp)
{
	int		i;
	int		x;
	char	**env;

	i = 0;
	x = 0;
	if (!ft_getenv(to_find, env_tmp))
		return (env_tmp);
	while (env_tmp[i])
		i++;
	env = malloc(sizeof(char *) * i);
	if (!env)
		return (NULL);
	i = 0;
	while (env_tmp[i])
	{
		if (!ft_strnstr(env_tmp[i], to_find, ft_strlen(to_find)))
		{
			env[x] = ft_strdup(env_tmp[i]);
			x++;
		}
		i++;
	}
	free_tab(env_tmp);
	return (env);
}

size_t ft_strcsnp(const char *s1, const char *c)
{
    int i;

    i = 0;
    while (s1[i] != '\0' && ft_strchr(c, s1[i]) == NULL)
        i++;
    return (i);
}

int print_export(char **env)
{
    int i;
    char *tmp;

    i = 0;
    tmp = NULL;
    while (env[i] && ft_strchr(env[i], '=') != 0)
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

// char	**ft_export(char **arg, char **env)
// {
// 	int	i;

// 	i = 0;
//     if (count_arg == 1)
//     {
//         return(print_export(env));
//     }
// 	if (count_arg > 1)
// 	{
// 	}
// }


int	main(int argc, char **argv, char **env_tmp)
{
	char **env;

	env = ft_str_tab_dup(env_tmp);
	print_export(env);
}