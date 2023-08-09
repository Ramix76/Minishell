/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:24:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/09 11:10:34 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_simple_command_do(char **job, t_data *data)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (ft_redirections_do(job, data) == EXIT_FAILURE
		|| ft_redirections_rm(job) == EXIT_FAILURE
		|| ft_simple_command(job, data) == EXIT_FAILURE)
		ret = EXIT_FAILURE;
	dup2(data->saved_out, STDOUT_FILENO);
	dup2(data->saved_in, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

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
