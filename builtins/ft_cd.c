/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:36:08 by bdany             #+#    #+#             */
/*   Updated: 2024/07/01 18:57:33 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
		return (1);
}

void	ft_puterr_endl(char *str)
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
	// if (count_arg(env) > 1)
	// {
	// 	ft_puterr_endl("bash: env: too many arguments");
	// 	return (1);
	// }
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	is_n_option(char *arg)
{
	int	i;

	i = 0;
	if (arg && !ft_strncmp(arg, "-n", 2))
	{
		i++;
		while (arg[i] && arg[i] == 'n')
			i++;
		if (!arg[i])
			return (1);
	}
	return (0);
}

void	print_without_new(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i + 1])
	{
		ft_putstr_fd(arg[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (arg[i])
		ft_putstr_fd(arg[i], 1);
}

void	print_with_new(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i + 1])
	{
		ft_putstr_fd(arg[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (arg[i])
		ft_putstr_fd(arg[i], 1);
	ft_putstr_fd("\n", 1);
}

int	ft_echo(char **arg)
{
	int	i;

	i = 1;
	while (arg[i] && is_n_option(arg[i]))
		i++;
	if (i != 1)
		print_without_new(arg + i);
	else
		print_with_new(arg + i);
	return (0);
}

char	*troncate_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
	{
		str[i + 1] = 0;
		return (str);
	}
	return (NULL);
}

char	*join_with_pwd(char **env, char *str)
{
	char	*old_pwd;
	char	*pwd;

	pwd = ft_getenv("PWD", env);
	old_pwd = ft_strjoin(str, pwd);
	free(str);
	return (old_pwd);
}

char	**put_pwd_in_old_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "OLDPWD=", 7))
		i++;
	if (env[i])
	{
		env[i] = troncate_equal(env[i]);
		env[i] = join_with_pwd(env, env[i]);
	}
	return (env);
}
char	*join_with_new_pwd(char *str)
{
	char	cwd[1024];
	char	*new_pwd;

	if (getcwd(cwd, sizeof(cwd)))
	{
		new_pwd = ft_strjoin(str, cwd);
		free(str);
		return (new_pwd);
	}
	return (NULL);
}

char	**update_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4))
		i++;
	if (env[i])
	{
		env[i] = troncate_equal(env[i]);
		env[i] = join_with_new_pwd(env[i]);
	}
	return (env);
}

char	**switch_pwd_env(char **env)
{
	env = put_pwd_in_old_pwd(env);
	env = update_pwd(env);
	return (env);
}

char	**ft_cd(char **arg, char **env)
{
	char	*home;

	if (count_arg(arg) == 2)
	{
		if (chdir(arg[1]))
			printf("bash: cd: %s: No such file or directory\n", arg[1]);
		else
			env = switch_pwd_env(env);
	}
	else if (count_arg(arg) == 1)
	{
		home = ft_getenv("HOME", env);
		if (!home)
			printf("bash: cd: HOME not set\n");
		else
		{
			chdir(home);
			env = switch_pwd_env(env);
		}
	}
	else
		printf("bash: cd: too many arguments\n");
	return (env);
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

size_t	ft_strcsnp(const char *s1, const char *c)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && ft_strchr(c, s1[i]) == NULL)
		i++;
	return (i);
}

int	cmp_env(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=' && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (0);
	if (s1[i] == '=')
		return (0);
	if (s2[i] == '=')
		return (1);
	if (s1[i] < s2[i])
		return (0);
	if (s1[i] > s2[i])
		return (1);
	return (0);
}

void	print_env_value(char *str)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	ft_putstr_fd("declare -x ", 1);
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		if (str[i] == '=')
		{
			ft_putchar_fd('\"', 1);
			equal = 1;
		}
		i++;
	}
	if (equal)
		ft_putchar_fd('\"', 1);
	ft_putchar_fd('\n', 1);
}

void	print_tab_int(int *tab, int size, char **env)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (i < size)
	{
		print_env_value(env[tab[i]]);
		i++;
	}
}

int	print_sort_env(char **env)
{
	int	*tab;
	int	size;
	int	i;
	int	j;
	int	rank;

	j = 0;
	size = count_arg(env);
	tab = malloc(sizeof(int) * size);
	while (j < size)
	{
		i = 0;
		rank = 0;
		while (env[i])
		{
			if (cmp_env(env[j], env[i]))
				rank++;
			i++;
		}
		tab[rank] = j;
		j++;
	}
	print_tab_int(tab, size, env);
	free(tab);
	return (0);
}

char	**realloc_env(char **env_tmp, int size)
{
	int		size_env;
	char	**env;
	int		i;

	i = 0;
	size_env = count_arg(env_tmp);
	env = malloc(sizeof(char *) * (size + size_env + 1));
	if (!env)
		return (NULL);
	while (env_tmp[i])
	{
		env[i] = ft_strdup(env_tmp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

// int	add_arg_to_env(char *str, char **env)
// {
// }

char	**add_env_variable(char **arg, char **env_tmp)
{
	int		size;
	int		i;
	char	**env;

	size = count_arg(arg);
	i = 0;
	env = realloc_env(env_tmp, size);
	free_tab(env_tmp);
	while (arg[i])
	{
		// add_arg_to_env(arg[i], env);
		i++;
	}
	return (NULL);
}

char	**ft_export(char **arg, char **env)
{
	// if (arg[0] == '_' && arg[1] == '\0')
	// return (0);
	if (count_arg(arg) == 1)
	{
		print_sort_env(env);
	}
	if (count_arg(arg) > 1)
	{
		// if (arg[0] == '_' && arg[1] == '\0')
		// 	return (0);
		env = add_env_variable(arg + 1, env);
	}
	return (NULL);
}

int	main(int argc, char **argv, char **env_tmp)
{
	char **env;

	env = ft_str_tab_dup(env_tmp);
	// print_sort_env(env);
	ft_echo(argv + 1);
	// // 	env = ft_unset(argv[1], env);
	env = ft_cd(argv + 1, env);
	ft_env(env);
	// env = ft_export(argv + 1, env);
}