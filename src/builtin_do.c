/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:31:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/08 11:40:29 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_do(t_cmd *cmd, t_data *data)
{
	char	*exec_name;

	exec_name = cmd->tokens[0];
	(void) data;
	(void) exec_name;
	return (EXIT_SUCCESS);
}

	//if (isbuiltin(exec_name) == EXIT_SUCCESS)
	// execute it
	//else
	//	return (EXIT_FAILURE);

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp(str, "echo", 4) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp(str, "env", 3) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
