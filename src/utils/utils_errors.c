/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:21:08 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/12 12:21:44 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_write_errors(const char *format, const char *directory)
{
	ft_fprintf(stderr, "minishell: cd: %s: ", directory);
	ft_fprintf(stderr, format);
}

static void	ft_export_write_errors(const char *format, const char *directory)
{
	ft_fprintf(stderr, "minishell: export: '%s': ", directory);
	ft_fprintf(stderr, format);
}

int	ft_error(int error, const char *directory)
{
	if (error == NO_SUCH_DIR)
		ft_cd_write_errors("No such file or directory\n", directory);
	else if (error == NO_PERMIT)
		ft_cd_write_errors("Permission denied\n", directory);
	else if (error == NO_DIR)
		ft_cd_write_errors("Not a directory\n", directory);
	else if (error == NO_HOME)
		ft_cd_write_errors("HOME not set\n", directory);
	else if (error == ERR_CD)
		ft_cd_write_errors("Failed to get current directory\n", directory);
	else if (error == ERR_PWD)
		ft_cd_write_errors("Failed to set PWD\n", directory);
	else if (error == ERR_OPWD)
		ft_cd_write_errors("Failed to set OLDPWD\n", directory);
	else if (error == ERR_FORMAT)
		ft_export_write_errors("not a valid identifier\n", directory);
	return (1);
}
