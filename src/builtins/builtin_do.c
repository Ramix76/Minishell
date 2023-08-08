/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:31:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/08 17:55:19 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_do(t_cmd *cmd, t_data *data)
{
	const char	*exec_name = cmd->tokens[0];

	if (ft_strcmp("pwd", exec_name) == 0)
		return (ft_pwd(data), EXIT_SUCCESS);
	else if (ft_strcmp("echo", exec_name) == 0)
		return (ft_echo(cmd, data), EXIT_SUCCESS);
	else if (ft_strcmp("cd", exec_name) == 0)
		return (ft_cd(cmd, data), EXIT_SUCCESS);
	else if (ft_strcmp("env", exec_name) == 0)
		return (ft_env(data), EXIT_SUCCESS);
	else if (ft_strcmp("unset", exec_name) == 0)
		return (ft_unset(cmd, data), EXIT_SUCCESS);
	else if (ft_strcmp("export", exec_name) == 0)
		return (ft_export(cmd, data), EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
