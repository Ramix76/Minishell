/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:36:55 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/08 12:01:53 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmd *cmd , t_data *data)
{
	if (cmd->tokens[1] != NULL)
	{
		while (cmd->tokens[1][i])
		{
			if (!ft_isdigit(cmd->tokens[1][i])

		}
	}

	printf("exit\n");
	g_running = 0;
	return (data->exit_code);
}
