/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:47:12 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/27 17:15:15 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

static void	write_errors(const char *format, const char *directory)
{

	ft_fprintf(stderr, "minishell: cd: %s: ", directory);
	ft_fprintf(stderr, format);
}

int	ft_error(int error, const char *directory)
{
	if (error == NO_SUCH_DIR)
		write_errors("No such file or directory\n", directory);
	else if (error == NO_PERMIT)
		write_errors("Permission denied\n", directory);
	else if (error == NO_DIR)
		write_errors("Not a directory\n", directory);
	else if (error == NO_HOME)
		write_errors("HOME not set\n", directory);
	else if (error == ERR_CD)
		write_errors("Failed to get current directory\n", directory);
	else if (error == ERR_PWD)
		write_errors("Failed to set PWD\n", directory);
	else if (error == ERR_OPWD)
		write_errors("Failed to set OLDPWD\n", directory);
	return (1);
}
