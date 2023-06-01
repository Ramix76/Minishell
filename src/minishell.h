/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/01 16:36:08 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


#include "builtin.h"

#include <sys/errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"

typedef struct s_cmd
{
	char	*command;
}				t_cmd;

#endif
