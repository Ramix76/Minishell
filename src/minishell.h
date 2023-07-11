/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/11 16:33:02 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>/* errno */
# include <limits.h>/* */
# include <stdio.h>/* readline, printf */
# include <stdlib.h>/* */
# include <string.h>/* */
# include <unistd.h>/* write, isatty */

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"/* */
# include "_minishell.h"/* */
# include "builtins.h"/* */

# define WR	1
# define RD	0

# define SH_NAME		"homersh"
# define PROMPT			"homersh$ "
# define SH_VERSION		"homersh, version 0.1-alpha"

# define METACHARACTERS	" \n\t|&;()<>\0"
# define OPERATORS		"\n|&;()<>"
# define CONTROLOP		"\n|&"
# define REDIRECTOP		"<>"

char	*ft_shell_expand(char *str, t_data *data);
int		ft_shell_do(t_data *data);
char	*ft_quotes_closed(char *line);
char	*ft_expand_quotes(char *line);

int		ft_job_control(char *line, t_data *data);
int		ft_command_do(char *line, t_data *data);

int		ft_pipe_do(char *line, t_data *data);

char	*ft_cmd_path(char *argv, const char **envp);
void	ft_free_str_arr(char **split);

int		ft_here_doc(char *limiter);
int		ft_read_stdin(int wr_fd, char *limiter);
int		ft_write_output(int fd, char *output);
int		ft_redirect_in(char *line, int *fd);

int		ft_execute_command(char *argv, char **envp, int *fd);

char	*ft_expand_dollar(char *expanded, char *dollar, t_data *data);

#endif /* minishell.h */
