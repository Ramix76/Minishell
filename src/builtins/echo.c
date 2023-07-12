/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:52:40 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/12 18:37:09 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echoed(char **tokens, int newline)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		ft_putstr_fd(tokens[i], 1);
		if (tokens[i + 1] && write(1, " ", 1) < 1)
		{
			printf("Error\n");
			return ;
		}
	}
	if (tokens == NULL || (newline && write(1, "\n", 1) < 0))
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	int		j;
	int		newline;

	i = 0;
	newline = 1;
	while (cmd->tokens[++i] && cmd->tokens[i][0] == '-'
		&& cmd->tokens[i][1] == 'n')
	{
		j = 1;
		while (cmd->tokens[i][j] == 'n')
			j++;
		if (!(cmd->tokens[i][j] == '\0'))
			break ;
		newline = 0;
	}
	ft_echoed(&cmd->tokens[i], newline);
	return (EXIT_SUCCESS);
}
