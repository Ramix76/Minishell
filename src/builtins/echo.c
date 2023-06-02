/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:32:57 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/02 15:48:32 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"


void	echo(const char *message, int newline)
{
	if (newline)
		printf("%s\n", message);
	else
		printf("%s", message);
}

void	ft_echo(t_cmd *cmd)
{
	int		newline;
	char	*message;

	newline = 1;
	message = cmd->tokens[1];
	if (cmd->tokens[1] && strcmp(cmd->tokens[1], "-n") == 0)
	{
		newline = 0;
		message = cmd->tokens[2];
	}
	echo(message, newline);
}
