/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/11 12:24:10 by mpuig-ma         ###   ########.fr       */
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
# include <termios.h>		/* avoid echoing */

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"			/* ... */
# include "_minishell.h"	/* t_data, t_cmd */

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS		0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE		1
# endif

# define SH_NAME			"homersh"
# define SH_VERSION			"version 0.1-alpha"
# define METACHARACTERS		" \n\t|<>&()"	// `;' not implemented

// consider allocating prompt in main.c -> data init
# define PROMPT				"homersh$ "

/* used for: <insert reason> */

extern int					g_in_heredoc;

/* builtins */

int		ft_builtin_do(t_cmd *cmd, t_data *data);
int		ft_env(t_data *data);
int		ft_echo(t_cmd *cmd, t_data *data);
int		ft_pwd(t_data *data);
int		ft_cd(t_cmd *cmd, t_data *data);
int		ft_unset(t_cmd *cmd, t_data *data);
int		ft_export(t_cmd *cmd, t_data *data);
int		ft_exit(t_cmd *cmd, t_data *data);

/* commands */

int		ft_shell_loop(t_data *data);
int		ft_shell_do(t_data *data, char *line);
int		ft_command_do(char **tokens, t_data *data);
int		ft_simple_command_do(char **job, t_data *data);
int		ft_sequence_do(char **tokens, int start, int end, t_data *data);
int		ft_parenthesis_do(char **tokens, int start, int end, t_data *data);
int		ft_pipeline(char **tokens, t_data *data);
int		ft_execute_command(t_cmd *cmd, t_data *data, int fork);

/* enviroment.c */

int		ft_init_env(char **envp, t_data *data);
int		ft_shlvl(char **envp, t_data *data);
int		ft_sethome(t_data *data);

/* expansions */

int		ft_shell_expand(char **tokens, t_data *data);
char	*ft_expand_tilde(char *line, t_data *data);
char	*ft_expand_dollar(char *expanded, t_data *data);
char	*ft_expand_wildcard(char *expanded, t_data *data);
char	*ft_expand_quotes(char *line, t_data *data);
char	*ft_quotes_closed(char *line);
char	*ft_getname(char *ptr);
char	*ft_getvalue(char *ptr, t_data *data);

/* parse */

char	**ft_parse2tokens(char *str);
char	**ft_parse_operators(char **tokens);
int		ft_syntax_check(char **tokens, t_data *data);
int		ft_syntax_parenthesis(char **tokens, int i);
int		ft_parenthesis_closed(char **tokens);

/* redirections */

int		ft_redirections_do(char **job, t_data *data);
int		ft_redirections_rm(char **job);
int		ft_reset_redirections(t_data *data);
int		ft_here_doc(char *limiter, t_data *data);
int		ft_in(char *op, char *value, t_data *data);
int		ft_out(char *op, char *value, t_data *data);

/* signals */

//void	ft_signal_handler(int signal);
//void	ft_handle_signals_heredoc(int signal);
void	ft_set_term(void);
int		ft_init_signals(int mode, t_data *data);

/* utils */

size_t	ft_arrlen(char **arr);
char	**ft_arrdup(char **arr);
char	**ft_arrndup(char **arr, size_t n);
void	ft_arr_rm_item(char **arr, int position);
char	*ft_cmd_path(char *argv, const char **envp);
void	ft_free_str_arr(char **split);
void	ft_error(const char *comd, const char *dir);
bool	ft_is_valid_var_format(const char *var);
void	ft_print_combined_vars(t_data *data);
void	ft_sort_vars(char **vars);
void	ft_print_sorted_vars(char **vars);
void	ft_free_vars(char **vars);
int		ft_cd_check_arguments(t_cmd *cmd);
char	*ft_concat_list(t_list *list);
int		ft_sort_list(t_list *list);
char	*ft_arr2str(char **arr);

#endif /* minishell.h */
