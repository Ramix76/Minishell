/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:02:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/05 10:44:34 by mpuig-ma         ###   ########.fr       */
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

# define PROMPT "homersh$ "

#endif /* minishell.h */
