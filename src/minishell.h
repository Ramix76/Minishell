/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/03 10:57:35 by mpuig-ma         ###   ########.fr       */
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

# define SH_NAME			"homersh"
# define PROMPT				"homersh$ "
# define SH_VERSION			"homersh, version 0.1-alpha"

# define METACHARACTERS		" \n\t|&;()<>"
# define OPERATORS			"\n|&;()<>"
# define CONTROLOP			"\n|&"
# define REDIRECTOP			"<>"

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
int		ft_env(t_data *data);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(t_data *data);
int		ft_cd(t_cmd *cmd, t_data *data);
int		ft_unset(t_cmd *cmd, t_data *data);
int		ft_export(t_cmd *cmd, t_data *data);

/* expansions */

int		ft_shell_expand(char **tokens, t_data *data);
char	*ft_expand_tilde(char *line, t_data *data);
char	*ft_expand_dollar(char *expanded, t_data *data);
char	*ft_expand_quotes(char *line, t_data *data);

/* job */

int		ft_shell_do(t_data *data);
int		ft_job_control(char *line, t_data *data);
int		ft_simple_command(char *job, t_data *data);
int		ft_redirections_do(char *job, t_data *data);
int		ft_redirections_rm(char *str);
int		ft_execute_command(t_cmd *cmd, t_data *data);
int		ft_here_doc(char *limiter);
int		ft_read_stdin(int wr_fd, char *limiter);
int		ft_write_output(int fd, char *output);
int		ft_redirect_in(char *line, int *fd);
int		ft_syntax_check(char **tokens);

/* signals */

void	ft_signal_handler(int signal);

/* utils */

char	*ft_cmd_path(char *argv, const char **envp);
void	ft_free_str_arr(char **split);
void	ft_error(const char *comd, const char *dir);
bool	ft_is_valid_var_format(const char *var);
char	**ft_strduparr(char **arr);
void	ft_print_combined_vars(t_data *data);
void	ft_sort_vars(char **vars);
void	ft_print_sorted_vars(char **vars);
void	ft_free_vars(char **vars);
int		ft_cd_check_arguments(t_cmd *cmd);

/* wildcard */
/* migrate to expansions/ */

char	**ft_files_and_dirs(void);

#endif /* minishell.h */
