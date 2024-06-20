#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	**arg;
	int		fd_in;
	int		fd_out;
	char	**env;
}			t_cmd;

typedef struct s_data
{
	int		**tab_fd;
}			t_data;

#endif