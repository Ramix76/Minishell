/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:40 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/07 17:44:54 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse to t_cmd
// execute comand (either builtin or not)
// all builtins should accept as arguments (t_cmd *cmd, t_data *data) ??

int	command_do(char *line, t_data *data)
{
	t_cmd	cmd;
	int		i;
	char	*cmd_str;

	i = 0;
	cmd.command = shell_expand(line);
	cmd.tokens = ft_split(line, ' ');
	cmd_str = ft_which(cmd.tokens[0], data->path);
	if (ft_strncmp(cmd.tokens[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd.tokens[0], "echo", 4) == 0)
		ft_echo(&cmd);
	else if (ft_strncmp(cmd.tokens[0], "env", 3) == 0)
		ft_env(data);
	else if (ft_strncmp(cmd.tokens[0], "exit", 4) == 0)
	{
		free(cmd_str);
		free_str_arr(cmd.tokens);
		exit(EXIT_SUCCESS);
	}
	else if (cmd_str == NULL)
	{
		ft_putstr_fd(SH_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(cmd.tokens[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	free(cmd_str);
	free_str_arr(cmd.tokens);
	return (EXIT_SUCCESS);
}

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
