/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/05 16:46:15 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <limits.h>
# include <stdio.h> /* readline, printf */
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "builtins.h"
# include "libft.h"

# define SH_NAME "homersh"
# define PROMPT "homersh$ "
# define SH_VERSION "homersh, version 0.1-alpha"

char	*shell_expand(char *str);

#endif /* minishell.h */
