/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/15 16:15:59 by mpuig-ma         ###   ########.fr       */
/*   Updated: 2023/06/08 15:13:07 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <limits.h>
# include <stdio.h> /* readline, printf */
# include <stdlib.h>
# include <string.h>
# include <unistd.h> /* write, isatty */

//# include "readline.h"
//# include "history.h"
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "_minishell.h"
# include "builtins.h"

# define WR	1
# define RD	0

# define SH_NAME		"homersh"
# define PROMPT			"homersh$ "
# define SH_VERSION		"homersh, version 0.1-alpha"

char	*shell_expand(char *str, t_data *data);
int		shell_do(t_data *data);
int		command_do(char *line, t_data *data);

int		pipe_do(char *line, t_data *data);

char	*cmd_path(char *argv, const char **envp);
void	free_str_arr(char **split);

#endif /* minishell.h */
