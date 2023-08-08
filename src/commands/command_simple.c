/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:24:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/08 16:27:19 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_simple_command(char **job, t_data *data)
{
	t_cmd	cmd;
	char	*exec;

	cmd.tokens = job;
	exec = *job;
	if (ft_strcmp("exit", exec) == 0)
		return (ft_exit(&cmd, data));
	else if (ft_builtin_do(&cmd, data) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		ft_execute_command(&cmd, data);
	return (EXIT_SUCCESS);
}
