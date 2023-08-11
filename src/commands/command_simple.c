/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:24:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/11 11:35:12 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_simple_command_do(char **job, t_data *data)
{
	int		ret;
	t_cmd	cmd;

	ret = EXIT_SUCCESS;
	cmd.tokens = job;
	if (ft_redirections_do(job, data) == EXIT_FAILURE
		|| ft_redirections_rm(job) == EXIT_FAILURE)
		ret = EXIT_FAILURE;
	if (ft_simple_command(&cmd, data) == EXIT_FAILURE)
		ret = EXIT_FAILURE;
	if (ft_strcmp("exit", *(cmd.tokens)) == 0)
		return (ft_exit(&cmd, data));
	return (ret);
}

int	ft_simple_command(t_cmd *cmd, t_data *data)
{
	if (ft_builtin_do(cmd, data) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		ft_execute_command(cmd, data);
	return (EXIT_SUCCESS);
}
