/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:43:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/11 16:25:10 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_simple_command(char *job, t_data *data);

int	ft_job_control(char *line, t_data *data)
{
	int		n;
	int		fd;
	char	*temp;
	char	*job;
	size_t	cspn;

	temp = line;
	fd = STDIN_FILENO;
	while (temp != NULL)
	{
		n = 0;
		cspn = ft_strcspn(temp + 1, CONTROLOP);
		job = ft_strndup(temp, cspn + 1);
		ft_redirect_in(job, &fd);
		if (*job == '|')
			n = ft_strspn(job, METACHARACTERS);
		temp = ft_strpbrk(temp + 1, CONTROLOP);
		ft_simple_command(job + n, data);
		free(job);
	}
	return (EXIT_SUCCESS);
}

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
		//else if (*temp == '<')
		temp = ft_strpbrk(temp + 1, REDIRECTOP);
	}
	//printf("job is \"%s\"\n", job + n);
	ft_command_do(job + n, data);
	return (EXIT_SUCCESS);
}

int	ft_command_do(char *line, t_data *data)
{
	t_cmd	cmd;
	char	*cmd_path;

	line = ft_shell_expand(line, data);
	cmd.tokens = ft_split(line, ' ');
	if (cmd.tokens[0] == NULL)
		return (ft_free_str_arr(cmd.tokens), EXIT_SUCCESS);
	cmd_path = ft_which(cmd.tokens[0], data->path);
	if (ft_is_builtin(cmd.tokens[0]) == EXIT_SUCCESS)
		ft_builtin_do(&cmd, data);
	else if (ft_strncmp(cmd.tokens[0], "exit", 4) == 0)
	{
		free(line);
		free(cmd_path);
		ft_free_str_arr(cmd.tokens);
		exit(EXIT_SUCCESS);
	}
	else if (cmd_path == NULL)
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd.tokens[0]);
	else
		ft_pipe_do(line, data);
	free(line);
	free(cmd_path);
	ft_free_str_arr(cmd.tokens);
	return (EXIT_SUCCESS);
}

int	ft_pipe_do(char *line, t_data *data)
{
	char	**pipe_split;
	int		fd;
	int		i;

	i = 0;
	fd = STDIN_FILENO;
	pipe_split = ft_split(line, '|');
	while (pipe_split[i] != NULL)
	{
		//if (ft_strchr(pipe_split[i], '<') != 0)
		//	ft_printf("redir\n");
		data->exit_code = ft_execute_command(pipe_split[i++], data->envp, &fd);
	}
	close(fd);
	ft_free_str_arr(pipe_split);
	return (EXIT_SUCCESS);
}
