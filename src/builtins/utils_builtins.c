/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:47:12 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/10 11:43:25 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

static void	cd_write_errors(const char *format, const char *directory)
{
	ft_fprintf(stderr, "minishell: cd: %s: ", directory);
	ft_fprintf(stderr, format);
}

static void	export_write_errors(const char *format, const char *directory)
{
	ft_fprintf(stderr, "minishell: export: '%s': ", directory);
	ft_fprintf(stderr, format);
}

int	ft_error(int error, const char *directory)
{
	if (error == NO_SUCH_DIR)
		cd_write_errors("No such file or directory\n", directory);
	else if (error == NO_PERMIT)
		cd_write_errors("Permission denied\n", directory);
	else if (error == NO_DIR)
		cd_write_errors("Not a directory\n", directory);
	else if (error == NO_HOME)
		cd_write_errors("HOME not set\n", directory);
	else if (error == ERR_CD)
		cd_write_errors("Failed to get current directory\n", directory);
	else if (error == ERR_PWD)
		cd_write_errors("Failed to set PWD\n", directory);
	else if (error == ERR_OPWD)
		cd_write_errors("Failed to set OLDPWD\n", directory);
	else if (error == ERR_FORMAT)
		export_write_errors("not a valid identifier\n", directory);
	return (1);
}
