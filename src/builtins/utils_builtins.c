/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:47:12 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/21 16:37:57 by framos-p         ###   ########.fr       */
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
	return (1);
}
