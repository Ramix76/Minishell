/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:30:49 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/11 13:13:29 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"
# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdbool.h>

# define NO_SUCH_DIR		1
# define NO_DIR				2
# define NO_PERMIT			3
# define NO_HOME			4
# define ERR_CD				5
# define ERR_PWD			6
# define ERR_OPWD			7
# define ERR_FORMAT			8

typedef struct s_cmd
{
	char	*command;
	char	**tokens;
	int		tokens_count;
}			t_cmd;

int		ft_builtin_do(t_cmd *cmd, t_data *data);
int		ft_is_builtin(char *str);

int		ft_env(t_data *data);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(t_data *data);
int		ft_cd(t_cmd *cmd, t_data *data);
void	ft_unset(char **var, t_data *data);
void	ft_export(t_cmd *cmd, t_data *data);

int		ft_error(int error, const char *directory);

#endif /* builtins.h */
