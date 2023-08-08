/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:44:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/08 15:52:03 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define START	0
#define END		1

static int		ft_getcommandlist(char **tokens, int *position);
//static int	ft_job_do(char **tokens, int start, int end, t_data *data);
//static int	ft_reset_redirections(t_data *data);

int	ft_command_do(char **tokens, t_data *data)
{
	int		i;
	int		list[2];
	bool	parenthesis;

	i = 0;
	parenthesis = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		list[START] = i;
		ft_getcommandlist(tokens, &i);
		if (tokens[i] == NULL)
			--i;
		list[END] = i;
		printf("start: %s, end: %s\n", tokens[list[START]], tokens[list[END]]);
		++i;
	}
	return (EXIT_SUCCESS);
	(void) data;
}

static int	ft_getcommandlist(char **tokens, int *position)
{
	int		i;
	bool	parenthesis;

	i = *position;
	parenthesis = false;
	while (tokens[i] != NULL)
	{
		if (parenthesis == false && ft_strcmp(tokens[i], "(") == 0)
			parenthesis = true;
		if (parenthesis == true && ft_strcmp(tokens[i], ")") == 0)
			parenthesis = false;
		if (tokens[i] != NULL && parenthesis == false
			&& (ft_strcmp(tokens[i], "&&") == 0
				|| ft_strcmp(tokens[i], "||") == 0))
			break ;
		++i;
	}
	*position = i;
	return (EXIT_SUCCESS);
}

/*
int	ft_command_do(char **tokens, t_data *data)
{
	t_cmd	cmd;
	char	*exec;

	cmd.tokens = job;
	exec = *job;
	if (ft_strcmp("exit", exec) == 0)
		return (ft_exit(&cmd, data));
	else if (ft_builtin_do(&cmd, data) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		ft_execute_command(&cmd, data);
	return (EXIT_SUCCESS);
}
*/

/*
int	ft_job_control(char **tokens, t_data *data)
{
	int		i;
	int		job[2];

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		job[START] = i;
		while (tokens[i] != NULL && ft_strcmp("|", tokens[i]) != 0)
			++i;
		if (tokens[i] == NULL)
			--i;
		if (*(tokens[i]) == '|')
			job[END] = i - 1;
		else
			job[END] = i;
		if (ft_job_do(tokens, job[START], job[END], data) == EXIT_FAILURE)
		{
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
*/

/*
static int	ft_job_do(char **tokens, int start, int end, t_data *data)
{
	size_t	arr_len;
	char	**job;

	arr_len = end - start + 1;
	job = ft_arrndup(tokens + start, arr_len);
	if (job == NULL)
	{
		errno = ENOMEM;
		return (EXIT_FAILURE);
	}
	if (ft_redirections_do(job, data) == EXIT_FAILURE
		|| ft_redirections_rm(job) == EXIT_FAILURE
		|| ft_command_do(job, data) == EXIT_FAILURE)
	{
		ft_free_arr(job);
		return (EXIT_FAILURE);
	}
	ft_free_arr(job);
	ft_reset_redirections(data);
	return (EXIT_SUCCESS);
}
*/

/*
static int	ft_reset_redirections(t_data *data)
{
	if (data->in != STDIN_FILENO)
		close(data->in);
	data->in = STDIN_FILENO;
	if (data->out != STDOUT_FILENO)
		close(data->out);
	data->out = STDOUT_FILENO;
	return (EXIT_SUCCESS);
}
*/

/*
int	ft_job_control(char *line, t_data *data)
{
	int		i;
	char	*job;
	char	**split;
	int		fd;
	int		fildes[2];
	pid_t	pid;

	i = 0;
	split = ft_split(line, '|');
	fd = STDIN_FILENO;
	while (split != NULL && split[i] != NULL)
	{
		job = ft_strtrim(split[i], " ");
		//if (dup2(fd, STDIN_FILENO) != STDIN_FILENO)
		//	close(fd);
		if (pipe(fildes) == -1)
		}
		{
			perror("pipe");
			exit(8);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("pipes");
			exit(9);
		}
		if (pid == 0)
		{
			//if (i > 0)
			//	dup2(fildes[WR], STDOUT_FILENO);
			//close(fildes[RD]);
			ft_simple_command(job, data);
			//close(fildes[WR]);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, NULL, 0);
		//close(fildes[WR]);
		//fd = fildes[RD];
		free(job);
		++i;
	}
	//close(fd);
	rl_redisplay();
	ft_free_arr(split);
	return (EXIT_SUCCESS);
}
*/
