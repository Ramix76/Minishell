/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:19:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/11 11:37:07 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_command(t_cmd *cmd, t_data *data)
{
	char	*exec;

	if (cmd->tokens[0] == NULL)
		return (EXIT_SUCCESS);
	if (cmd->tokens[0][0] != '.' && cmd->tokens[0][0] != '/')
		exec = ft_which(cmd->tokens[0], data->path);
	else
		exec = ft_realpath(cmd->tokens[0], NULL);
	if (exec == NULL)
	{
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd->tokens[0]);
		data->exit_code = 127;
		return (EXIT_FAILURE);
	}
	ft_execvpe(exec, (char const **) cmd->tokens, (const char **) data->envp);
	return (EXIT_SUCCESS);
}
