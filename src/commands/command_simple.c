/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:24:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/11 12:04:47 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_simple_command(t_cmd *cmd, t_data *data);

int	ft_simple_command_do(char **job, t_data *data)
{
	int		ret;
	t_cmd	cmd;

	ret = EXIT_SUCCESS;
	cmd.tokens = job;
	if (ft_redirections_do(job, data) == EXIT_FAILURE
		|| ft_redirections_rm(job) == EXIT_FAILURE)
		ret = EXIT_FAILURE;
	if (ft_strcmp("exit", *(cmd.tokens)) == 0)
		return (ft_exit(&cmd, data));
	if (ft_simple_command(&cmd, data) == EXIT_FAILURE)
		ret = EXIT_FAILURE;
	return (ret);
}

static int	ft_simple_command(t_cmd *cmd, t_data *data)
{
	if (ft_builtin_do(cmd, data) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (data->pipe == 1)
		ft_execute_command(cmd, data, 0);
	else
		ft_execute_command(cmd, data, 1);
	return (EXIT_SUCCESS);
}
