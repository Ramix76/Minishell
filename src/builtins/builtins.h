/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:30:49 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/21 16:00:52 by framos-p         ###   ########.fr       */
/*   Updated: 2023/06/08 15:13:10 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"
# include <dirent.h>

# define	NO_SUCH_DIR			1
# define	NO_DIR				2
# define	NO_PERMIT			3

typedef struct s_cmd
{
	char	*command;
	char	**tokens;
	int		tokens_count;
}			t_cmd;

int		builtin_do(t_cmd *cmd, t_data *data);
int		is_builtin(char *str);

int		ft_env(t_data *data);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(void);
int		ft_cd(t_cmd *cmd, t_data *data);

int		ft_error(int error, const char *directory);

#endif /* builtins.h */
