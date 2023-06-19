/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:40 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/15 17:58:29 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse to t_cmd
// execute comand (either builtin or not)
// all builtins should accept as arguments (t_cmd *cmd, t_data *data) ??

int	command_do(char *line, t_data *data)
{
	t_cmd	cmd;
	char	*cmd_path;

	line = shell_expand(line, data);
	cmd.command = shell_expand(line, data);
	cmd.tokens = ft_split(line, ' ');
	if (cmd.tokens[0] == NULL)
		return (free_str_arr(cmd.tokens), EXIT_SUCCESS);
	cmd_path = ft_which(cmd.tokens[0], data->path);
	if (is_builtin(cmd.tokens[0]) == EXIT_SUCCESS)
		builtin_do(&cmd, data);
	else if (ft_strncmp(cmd.tokens[0], "exit", 4) == 0)
	{
		free(line);
		free(cmd_path);
		free_str_arr(cmd.tokens);
		exit (EXIT_SUCCESS);
	}
	else if (cmd_path == NULL)
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd.tokens[0]);
	else
		pipe_do(line, data);
	free(line);
	free(cmd_path);
	free_str_arr(cmd.tokens);
	return (EXIT_SUCCESS);
}
