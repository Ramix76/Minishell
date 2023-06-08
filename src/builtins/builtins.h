/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:30:49 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/08 11:51:49 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

typedef struct s_cmd
{
	char	*command;
	char	**tokens;
}			t_cmd;

int			builtin_do(t_cmd *cmd, t_data *data);
int			is_builtin(char *str);

int			ft_echo(t_cmd *cmd);
int			ft_pwd(void);
int			ft_env(void *data);

#endif /* builtins.h */
