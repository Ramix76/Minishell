/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:43:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/31 13:37:20 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_simple_command(char *job, t_data *data);
int			ft_perform_redirections(char *job, t_data *data);

int	ft_job_control(char *line, t_data *data)
{
	int		i;
	char	*job;
	char	**split;

	i = 0;
	split = ft_split(line, '|');
	while (split != NULL && split[i] != NULL)
	{
		job = ft_strtrim(split[i], " ");
		ft_simple_command(job, data);
		free(job);
		++i;
	}
	ft_free_arr(split);
	return (EXIT_SUCCESS);
}

static int	ft_simple_command(char *job, t_data *data)
{
	printf("will execute: %s\n", job);
	if (ft_perform_redirections(job, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_command_do(job, data);
	return (EXIT_SUCCESS);
}

int	ft_perform_redirections(char *job, t_data *data)
{
	int		i;
	char	*token;
	char	**tokens;

	i = 0;
	(void) data;
	tokens = ft_parse2tokens(job);
	while (tokens != NULL && tokens[i] != NULL)
	{
		token = tokens[i];
		if (*token == 074 || *token == 076)
			printf("alert: %s\n", token);
		++i;
	}
	ft_free_arr(tokens);
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
