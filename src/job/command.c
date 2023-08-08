/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:44:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/08 12:01:55 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_command_do(char **job, t_data *data)
{
	t_cmd	cmd;
	char	*exec;

	cmd.tokens = job;
	exec = *job;
	if (ft_strcmp("exit", exec) == 0)
		return (ft_exit(data), EXIT_SUCCESS);
	else if (ft_builtin_do(&cmd, data) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		ft_execute_command(&cmd, data);
	return (EXIT_SUCCESS);
}
