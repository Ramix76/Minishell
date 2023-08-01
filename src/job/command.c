/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:44:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/01 10:09:17 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_simple_command(char *job, t_data *data)
{
	if (ft_redirections_do(job, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_redirections_rm(job);
	ft_command_do(ft_strtrim(job, " "), data);
	return (EXIT_SUCCESS);
}

int	ft_command_do(char *job, t_data *data)
{
	t_cmd	cmd;
	char	*exec;

	printf("ft_command_do> %s\n", job);
	(void) data;
	cmd.tokens = ft_split(job, ' ');
	if (cmd.tokens == NULL)
		return (EXIT_SUCCESS);
	exec = cmd.tokens[0];
	return (EXIT_SUCCESS);
}

/*
// falta append job to cmd_path ??
int	ft_command_do(char *job, t_data *data)
{
	t_cmd	cmd;
	char	*cmd_path;

	printf("will execute: %s\n", job);
	cmd.tokens = ft_split(job, ' ');
	if (cmd.tokens[0] == NULL)
		return (ft_free_str_arr(cmd.tokens), EXIT_SUCCESS);
	if (cmd.tokens[0][0] != '.' && cmd.tokens[0][0] != '/')
		cmd_path = ft_which(cmd.tokens[0], data->path);
	else
		cmd_path = ft_realpath(cmd.tokens[0], NULL);
	if (ft_strcmp("exit", cmd.tokens[0]) == 0)
	{
		free(job);
		free(cmd_path);
		ft_free_str_arr(cmd.tokens);
		exit(EXIT_SUCCESS);
	}
	else if (ft_builtin_do(&cmd, data) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (cmd_path == NULL)
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd.tokens[0]);
	else
	{
		ft_pipe_do(cmd_path, data);
	}
	free(cmd_path);
	ft_free_str_arr(cmd.tokens);
	return (EXIT_SUCCESS);
}
*/
