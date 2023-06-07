/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:40 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/07 13:38:40 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_do(char *line, t_data *data)
{
	t_cmd	cmd;
	int		i;
	char	*cmd_str;

	i = 0;
	cmd.command = shell_expand(line);
	cmd.tokens = ft_split(line, ' ');
	cmd_str = cmd_path(cmd.tokens[0], (const char **) data->envp);
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
	else
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
