/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:31:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/15 13:39:15 by mpuig-ma         ###   ########.fr       */
/*   Updated: 2023/06/12 15:27:06 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_do(t_cmd *cmd, t_data *data)
{
	const char	*exec_name = cmd->tokens[0];

	if (ft_strncmp(exec_name, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(exec_name, "echo", 4) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(exec_name, "cd", 2) == 0)
		ft_cd(cmd, data);
	else if (ft_strncmp(exec_name, "env", 3) == 0)
		ft_env(data);
	return (EXIT_SUCCESS);
}

int	is_builtin(char *str)
{
	if (str == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp(str, "echo", 4) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp(str, "cd", 2) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp(str, "env", 3) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
