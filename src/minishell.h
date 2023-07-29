/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/29 15:10:26 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>			/* errno */
# include <limits.h>		/* */
# include <stdio.h>			/* readline, printf */
# include <stdlib.h>		/* */
# include <string.h>		/* */
# include <unistd.h>		/* write, isatty */
# include <fstab.h>			/* _PATH_FSTAB */
# include <stdbool.h>		/* booleans */
# include <sys/stat.h>		/* lstat */
# include <dirent.h>		/* opendir, closedir */
# include <signal.h>		/* signal handling */

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"			/* */
# include "_minishell.h"	/* t_data, t_cmd */

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS		0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE		1
# endif

/* CONSIDER moving WR RD to file pipes */

# define WR					1
# define RD					0

# define SH_NAME			"homersh"
# define PROMPT				"homersh$ "
# define SH_VERSION			"homersh, version 0.1-alpha"

# define METACHARACTERS		" \n\t|&;()<>\0"
# define OPERATORS			"\n|&;()<>"
# define CONTROLOP			"\n|&"
# define REDIRECTOP			"<>"

/*
 * PLEASE, replace macro strings with errno and perror();
 * VERY THANK YOU
 */

# define NO_SUCH_DIR		2
# define NO_SUCH_DIR_MSG	"No such file or diectory" // ENOENT
# define NO_DIR				3
# define NO_DIR_MSG			"Not a directory" // same as ENOENT?
# define NO_PERMIT			4
# define NO_PERMIT_MSG		"Permission denied" // EACCES
# define NO_HOME			5
# define NO_HOME_MSG		"HOME not set"
# define ERR_CD				6
# define ERR_CD_MSG			"Failed to get current directory"
# define ERR_PWD			7
# define ERR_PWD_MSG		"Failed to set PWD"
# define ERR_OPWD			8
# define ERR_OPWD_MSG		"Failed to set OLDPWD"
# define ERR_FORMAT			9
# define ERR_FORMAT_MSG		"not a valid identifier"

/* used for: <insert reason> */

extern sig_atomic_t			g_running;

/* enviroment.c */

int		ft_init_env(char **envp, t_data *data);
int		ft_shlvl(char **envp, t_data *data);
int		ft_sethome(t_data *data);

/* parse.c */

char	**ft_parse2tokens(char *str);

/* builtins */

int		ft_builtin_do(t_cmd *cmd, t_data *data);
int		ft_is_builtin(char *str);
int		ft_env(t_data *data);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(t_data *data);
int		ft_cd(t_cmd *cmd, t_data *data);
int		ft_unset(t_cmd *cmd, t_data *data);
int		ft_export(t_cmd *cmd, t_data *data);

/* commands */

int		ft_execute_command(char *argv, char **envp, int *fd);
int		ft_shell_do(t_data *data);
int		ft_job_control(char *line, t_data *data);
int		ft_command_do(char *line, t_data *data);
int		ft_pipe_do(char *line, t_data *data);

/* expansions */

char	*ft_shell_expand(char *str, t_data *data);
char	*ft_expand_tilde(char *line, t_data *data);
char	*ft_expand_dollar(char *expanded, t_data *data);
char	*ft_expand_quotes(char *line, t_data *data);

/* redirections */

int		ft_here_doc(char *limiter);
int		ft_read_stdin(int wr_fd, char *limiter);
int		ft_write_output(int fd, char *output);
int		ft_redirect_in(char *line, int *fd);

/* utils */

char	*ft_cmd_path(char *argv, const char **envp);
void	ft_free_str_arr(char **split);
void	ft_error(int error, const char *command, const char *directory);
bool	ft_is_valid_var_format(const char *var);
char	**ft_strduparr(char **arr);
void	ft_print_combined_vars(t_data *data);
void	ft_sort_vars(char **vars);
void	ft_print_sorted_vars(char **vars);
void	ft_free_vars(char **vars);
int		ft_cd_check_arguments(t_cmd *cmd);

/* signals */

void	ft_signal_handler(int signal);

/* wildcard */

char	**ft_files_and_dirs(void);

#endif /* minishell.h */
