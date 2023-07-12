/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/12 12:12:21 by framos-p         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/stat.h>
# include <dirent.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"/* */
# include "_minishell.h"/* */

# define WR					1
# define RD					0
# define NO_SUCH_DIR		2
# define NO_DIR				3
# define NO_PERMIT			4
# define NO_HOME			5
# define ERR_CD				6
# define ERR_PWD			7
# define ERR_OPWD			8
# define ERR_FORMAT			9

# define SH_NAME		"homersh"
# define PROMPT			"homersh$ "
# define SH_VERSION		"homersh, version 0.1-alpha"

char	*ft_shell_expand(char *str, t_data *data);
int		ft_shell_do(t_data *data);
char	*ft_quotes_closed(char *line);
char	*ft_expand_quotes(char *line);

int		ft_job_control(char *line, t_data *data);
int		ft_command_do(char *line, t_data *data);

int		ft_pipe_do(char *line, t_data *data);

char	*ft_cmd_path(char *argv, const char **envp);
void	ft_free_str_arr(char **split);

int		ft_builtin_do(t_cmd *cmd, t_data *data);
int		ft_is_builtin(char *str);

int		ft_env(t_data *data);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(t_data *data);
int		ft_cd(t_cmd *cmd, t_data *data);
void	ft_unset(char **var, t_data *data);
void	ft_export(t_cmd *cmd, t_data *data);

int		ft_error(int error, const char *directory);
void	ft_print_sorted_env(char **envp_copy);
void	ft_sorting_env(char **arr, size_t size);

#endif /* minishell.h */
