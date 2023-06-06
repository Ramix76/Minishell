/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:30:49 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/06 16:46:01 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_cmd
{
	char		*command;
	char		**tokens;
}				t_cmd;

int		ft_echo(t_cmd *cmd);
int		ft_pwd(void);

#endif /* builtins.h */
