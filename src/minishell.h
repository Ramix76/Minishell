/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/07 13:37:21 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <limits.h>
# include <stdio.h> /* readline, printf */
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "builtins.h"

typedef struct s_data
{
	char	*path;
	char	**envp;
	int		exit_code;
}			t_data;

# define SH_NAME "homersh"
# define PROMPT "homersh$ "
# define SH_VERSION "homersh, version 0.1-alpha"

char	*shell_expand(char *str);
int		shell_do(t_data *data);
int		command_do(char *line, t_data *data);

char	*cmd_path(char *argv, const char **envp);
void	free_str_arr(char **split);

#endif /* minishell.h */
