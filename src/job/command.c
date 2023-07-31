/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:44:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/31 16:08:15 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_simple_command(char *job, t_data *data)
{
	printf("will execute: %s\n", job);
	if (ft_perform_redirections(job, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//ft_clean
	ft_command_do(job, data);
	return (EXIT_SUCCESS);
}

/*
static int	ft_simple_command(char *job, t_data *data)
{
	int		n;
	char	*temp;

	n = 0;
	temp = ft_strpbrk(job, REDIRECTOP);
	while (temp != NULL)
	{
		if (ft_strncmp(temp, "<< ", 3) == 0)
		{
			ft_here_doc("--");
			temp += 3;
		}
		temp = ft_strpbrk(temp + 1, REDIRECTOP);
	}
	ft_command_do(job + n, data);
	return (EXIT_SUCCESS);
}
*/

// falta append line to cmd_path
int	ft_command_do(char *line, t_data *data)
{
	t_cmd	cmd;
	char	*cmd_path;

	cmd.tokens = ft_split(line, ' ');
	if (cmd.tokens[0] == NULL)
		return (ft_free_str_arr(cmd.tokens), EXIT_SUCCESS);
	if (cmd.tokens[0][0] != '.' && cmd.tokens[0][0] != '/')
		cmd_path = ft_which(cmd.tokens[0], data->path);
	else
		cmd_path = ft_realpath(cmd.tokens[0], NULL);
	if (ft_strcmp("exit", cmd.tokens[0]) == 0)
	{
		free(line);
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
