/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:36:48 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/09 17:31:54 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define START	0
#define END		1
#define WR		1
#define RD		0

static int	ft_getpipelines(char **tokens, int *position);
static int	ft_pipe_do(char **tokens, int start, int end, t_data *data);

int	ft_pipeline(char **tokens, t_data *data)
{
	int	i;
	int	pipeline[2];

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		pipeline[START] = i;
		ft_getpipelines(tokens, &i);
		if (ft_strcmp(tokens[i], "|") == 0)
			pipeline[END] = i - 1;
		else
			pipeline[END] = i;
		data->saved_in = dup(STDIN_FILENO);
		dup2(data->in, STDIN_FILENO);
		ft_pipe_do(tokens, pipeline[START], pipeline[END], data);
		dup2(data->saved_in, STDIN_FILENO);
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	ft_getpipelines(char **tokens, int *position)
{
	int	i;

	i = *position;
	while (tokens[i] != NULL && ft_strcmp(tokens[i], "|") != 0)
		++i;
	if (tokens[i] == NULL)
		--i;
	*position = i;
	return (EXIT_SUCCESS);
}

static int	ft_pipe_do(char **tokens, int start, int end, t_data *data)
{
	int		pipefd[2];
	pid_t	pid;
	size_t	arr_len;
	char	**job;

	arr_len = end - start + 1;
	job = ft_arrndup(tokens + start, arr_len);
	if (job == NULL)
		return (errno = ENOMEM, EXIT_FAILURE);
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[RD]);
		dup2(pipefd[WR], STDOUT_FILENO);
		if (ft_simple_command_do(job, data) == EXIT_FAILURE)
			return (ft_free_arr(job), EXIT_FAILURE);
		close(pipefd[WR]);
		exit(data->exit_code);
	}
	waitpid(pid, &data->exit_code, 0);
	close(pipefd[WR]);
	data->in = pipefd[RD];
	return (EXIT_SUCCESS);
}
